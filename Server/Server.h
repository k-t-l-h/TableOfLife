#include <vector>
#include "../ParserToGA/ParserToGA.cpp"
#include "../Request/Request.h"
#include "../Result/Result.h"
#include "../Manager/Manager.h"
#include "../Reporter/Reporter.h"
#include "../Adapter/Adapter.cpp"

#include "../General/General.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/thread.hpp>
#include <algorithm>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>

#ifndef TABLEOFLIFE_SERVER_H
#define TABLEOFLIFE_SERVER_H


namespace u = boost::uuids;

class Session {
public:
    boost::asio::streambuf response_;
    std::string body;
    Session(boost::asio::io_service& io_service, General *gen) : socket_(io_service), gen_(gen),timer_(io_service) {}

    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }

    void start() {
        started_ = true;
        last_ping = boost::posix_time::microsec_clock::local_time();
        do_read();
    }

    void stop() {
        if ( !started_) return;
        started_ = false;
        socket_.close();
    }

    bool started() const { return started_; }

    int id() const { return id_; }

private:
    void do_read() {
        // увеличим буфер
        response_.prepare(1024);
        boost::asio::mutable_buffers_1 bufs = response_.prepare(1024);
        size_t n = socket_.receive(bufs);
        response_.commit(n);

        async_read_until(socket_, response_,"\0",
                   boost::bind(&Session::handle_read_body, this,
                               boost::asio::placeholders::error));
        life_timer();
    }

    void on_error() {
        do_write("error Invalid request\r\n");
    }

    void on_report(std::string request) {
        std::stringstream ss;
        ss << request.substr(4, request.size() - 4);
        int id = -1;
        try {
            ss >> id;
        } catch (std::stringstream::failure& e) {
            std::cout << request << std::endl;
            std::cerr << "Invalid id\n";
        }
        if (id == -1) {
            do_write("error id\r\n\r\n");
            return;
        }
        auto report = gen_->sendAnswer(id);
        if (report.first) {
            if (report.second.size() == 0)
                do_write("error Invalid test\r\n\r\n");
            else
                do_write("report " + report.second + "\r\n\r\n");
        } else if (id_ == id)
            do_write("wait\r\n\r\n");
        else
            do_write("error Non\r\n\r\n");
    }

    void on_test(std::string request) {
        srand(time(NULL));
        int id = rand();
        id_ = id;
        std::string str_id = std::to_string(id);
        gen_->getRequest("{    \"request\": {    \"id\": \"" + str_id + "\",    " + request.substr(5, request.size()-5) + "    }}");
        do_write("id " + str_id + " \r\n\r\n");
    }

    u::uuid get_str(std::string header){
        try {
            u::string_generator string_gen;
            return string_gen(header);
        } catch (std::exception& e) {
            u::nil_generator nil_gen;
            return nil_gen();
        }
    }

    void handle_read_body(const boost::system::error_code& err) {
        if (!err) {
            std::istream response_stream(&response_);
            std::string b;
            while (std::getline(response_stream, b) && b != "\0")
                body += b;
            if (body.substr(0, 4) == "POST") {
                body = body.substr(body.find("{"), body.size()-1);
                gen_->getRequest(body);
            } else if ((body.substr(0, 3) == "GET")) {
                std::string header;
                if (body.substr(4,8) == "/status/") {
                    u::uuid uuid = get_str(body.substr(12, 36));
                    if (uuid.is_nil()) {
                        on_error();
                        return;
                    }
                    Adapter adpter;
                    adpter.GetResult(uuid); // возвращет структуру
//                    if (структура пуста то) {
//                        on_error();
//                        return;
//                    }
                }
            }

//                .. вызывает славин метод
            std::cout << body;
            stop(); // временно
        } else
            on_error();
    }



    void do_write(const std::string& msg) {
        if (!started()) return;
        std::copy(msg.begin(), msg.end(), writeBuffer_);
        socket_.async_write_some(boost::asio::buffer(writeBuffer_, msg.size()),
                                 boost::bind(&Session::handle_write, this,
                                             boost::asio::placeholders::error));
    }

    void handle_write(const boost::system::error_code& error) {
        if (!error)
            do_read();
        else
            stop();
    }

    void on_check_life() {
        boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
        if ( (now - last_ping).total_milliseconds() > 50000) stop();
        last_ping = boost::posix_time::microsec_clock::local_time();
    }

    void life_timer() {
        timer_.expires_from_now(boost::posix_time::millisec(50000));
        timer_.async_wait( boost::bind(&Session::on_check_life, this));
    }

private:
    boost::asio::ip::tcp::socket socket_;
    General *gen_;
    boost::asio::deadline_timer timer_;
    enum { max_length = 2048 };
    char data_[max_length];
    char readBuffer_[max_length];
    char writeBuffer_[max_length];
    bool started_;
    boost::posix_time::ptime last_ping;
    int id_ = -1;
};

class Server {
public:
    std::string returnBodyStr;
    std::string * DataJson;


    Server(boost::asio::io_service &io_service, short port, General *gen) : io_service_(io_service),
    acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    gen_(gen), DataJson(nullptr) {
        Session *new_session = new Session(io_service_, gen_);
        acceptor_.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
    }
    ;
    Server(const Server&) = delete;
    ~Server() = default;

    void handle_accept(Session *new_session,
                       const boost::system::error_code &error) {
        if (!error) {
            new_session->start();
            sessions.push_back(new_session);
            new_session = new Session(io_service_, gen_);
            acceptor_.async_accept(new_session->socket(),
                                   boost::bind(&Server::handle_accept, this, new_session,
                                               boost::asio::placeholders::error));
        } else {
            std::cout << "error\n";
            delete new_session;
        }
    }

    int Run(); // слушает реквесты

    int SendStrParser(int id); // отправка json пользователю

    void TakeAdapter(int id); //

    int SendAnswer();

    void PackReqParser();

private:

    boost::asio::io_service &io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
    General *gen_;
    std::vector<Session *> sessions;

};

#endif //TABLEOFLIFE_SERVER_H
