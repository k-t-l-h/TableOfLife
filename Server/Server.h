#include "../ParserToHuman/ParserToHuman.h"
#include "../Request/Request.h"
#include "../Result/Result.h"
#include "../Manager/Manager.h"
#include "../Adapter/Adapter.h"
#include "../General/General.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <vector>
#include <string>

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H

namespace u = boost::uuids;

class Session {
private:
    boost::asio::ip::tcp::socket socket_;
    General *gen_;
    boost::asio::deadline_timer timer_;
    boost::posix_time::ptime last_ping;

public:
    boost::asio::streambuf response_;
    std::string body;
    Session(boost::asio::io_service& io_service, General *gen)
        : socket_(io_service), gen_(gen), timer_(io_service) {}

    boost::asio::ip::tcp::socket& socket() { return socket_; }

    void start() {
        last_ping = boost::posix_time::microsec_clock::local_time();
        do_read();
    }

    void stop() {
        socket_.close();
    }

private:
    void do_read() {
        // увеличим буфер
        response_.prepare(1024);
        boost::asio::mutable_buffers_1 bufs = response_.prepare(1024);
        size_t n = socket_.receive(bufs);
        response_.commit(n);

        async_read_until(socket_, response_, "\0",
                         boost::bind(&Session::handle_read_body, this,
                                     boost::asio::placeholders::error));
        life_timer();
    }

    static u::uuid get_uuid(const std::string& header) {
        try {
            u::string_generator string_gen;
            return string_gen(header);
        } catch (std::exception &e) {
            u::nil_generator nil_gen;
            return nil_gen();
        }
    }

    void handle_read_body(const boost::system::error_code &err) {
        if (!err) {
            std::istream response_stream(&response_);
            std::string header;
            std::string h;
            int length;

            while (std::getline(response_stream, h) && h != "\r\n\r\n") {
                if (h.find("Content-Length:") != -1) {
                    length = std::stoi(h.substr(h.find(' '), h.find(' ') - h.find('\r')));
                    break;
                }
                header += h;
            }

            // API
            if (header.find("POST") != -1) {
                if (header.find("/create/ ") != -1) {
                    std::string line;
                    int counter = 0;
                    while (std::getline(response_stream, line) && counter != length) {
                        body += line;
                        counter++;
                    }

                    u::random_generator gen;
                    u::uuid uuid = gen();

                    if (gen_->getRequest(line, uuid) == -1) { // если что поменять на body
                        SendRequest(R"({"error": "Parser error"})", "400 Bad Request");
                    }
                    else {
                        SendRequest(R"({"UUID": ")" +
                            std::string(boost::uuids::to_string(uuid)) + "\"}", "201 Created");
                    }
                } else {
                    SendRequest(R"({"error": "Incorrect API"})", "404 Not Found");
                }
            } else if ((header.find("GET") != -1)) {
                if (header.find("/status/") != -1) {
                    u::uuid uuid = get_uuid(
                        header.substr(header.find(' ') + 9, 36));  // UUID 36 symbol
                    if (uuid.is_nil()) {
                        std::string u_id;
                        int pos = 12;
                        while (header[pos] != ' ') {
                            u_id += header[pos];
                            pos++;
                        }
                        SendRequest(R"({"error": "Invalid )" + u_id + "\"}", "400 Bad Request");
                        return;
                    }

                    Adapter adapter(gen_->ptr_db());

                    Result res = adapter.GetResult(uuid); // возвращет

                    if (res.result.empty()) {
                        SendRequest(R"({"error": "Does not exists"})", "404 Not Found");
                        return;
                    }
                    ParserToHuman parse;
                    std::string jsonR = parse.GetReadable(res);
                    SendRequest(jsonR, "200 OK");

                } else {
                    SendRequest(R"({"error": "Incorrect API"})", "404 Not Found");
                }
            } else {
                SendRequest(R"({"error": "Method Not Allowed"})", "405 Method Not Allowed");
            }
        } else
            SendRequest(R"({"error": "Broke server"})", "500 Internal Server Error");
    }

    void SendRequest(const std::string& str, const std::string& status_code) {
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "HTTP/1.1 " << status_code << "\r\n";
        request_stream << "Connection: close\r\n";
        request_stream << "Content-Type: application/json\r\n";
        request_stream << "Content-Length: " << str.size();
        request_stream << "\r\n\r\n";
        request_stream << str;
        boost::asio::write(socket_, request);
    }

    void on_check_life() {
        boost::posix_time::ptime now =
            boost::posix_time::microsec_clock::local_time();
        if ((now - last_ping).total_milliseconds() > 50000) stop();
        last_ping = boost::posix_time::microsec_clock::local_time();
    }

    void life_timer() {
        timer_.expires_from_now(boost::posix_time::millisec(50000));
        timer_.async_wait(boost::bind(&Session::on_check_life, this));
    }
};

class Server {
public:
    Server(boost::asio::io_service& io_service, short port, General *gen)
        : io_service_(io_service),
          acceptor_(io_service, boost::asio::ip::tcp::endpoint(
              boost::asio::ip::tcp::v4(), port)),
          gen_(gen) {
        Session* new_session = new Session(io_service_, gen_);
        acceptor_.async_accept(
            new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session,
                        boost::asio::placeholders::error));
    };

    Server(const Server&) = delete;
    ~Server() = default;

    void handle_accept(Session *new_session,
                       const boost::system::error_code& error) {
        if (!error) {
            new_session->start();
            sessions.push_back(new_session);
            new_session = new Session(io_service_, gen_);
            acceptor_.async_accept(
                new_session->socket(),
                boost::bind(&Server::handle_accept, this, new_session,
                            boost::asio::placeholders::error));
        } else {
            std::cout << "error\n";
            delete new_session;
        }
    }

private:
    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    General *gen_;
    std::vector<Session *> sessions;
};

#endif  // TABLEOFLIFE_SERVER_H
