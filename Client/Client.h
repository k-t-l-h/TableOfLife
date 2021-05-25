#ifndef TABLEOFLIFE_TABLEOFLIFE_CLIENT_CLIENT_H
#define TABLEOFLIFE_TABLEOFLIFE_CLIENT_CLIENT_H

#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <ctime>
#include <memory>
#include <string>

class Client : public std::enable_shared_from_this<Client> {
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::address address;
    int port;
    bool status = false;
    char buffer[2048];

public:
    Client(boost::asio::io_context& io, const std::string& address, int port)
        : socket(io),
          address(boost::asio::ip::address::from_string(address)),
          port(port) {}

    void start() {
        try {
            socket.connect(boost::asio::ip::tcp::endpoint(address, port));
            status = true;
            std::cout << "Connection with " << address.to_string() << ":" << port
                      << std::endl;
        } catch (boost::system::system_error& e) {
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    void close() {
        try {
            socket.close();
            status = false;
        } catch (boost::system::system_error& e) {
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    void send(const std::string& message) {
        boost::asio::streambuf request;
        try {
            boost::asio::write(socket,
                               boost::asio::buffer(message.data(), message.size()));
        } catch (boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
        }
    }

    std::string read() {
        std::string result;
        int bytes = 0;
        std::string tmp;
        try {
            bytes = boost::asio::read(
                socket, boost::asio::buffer(buffer, 2048),
                [this](const boost::system::error_code& err, size_t byte) {
                    if (err) return false;
                    std::string tmp(this->buffer, this->buffer + byte);
                    int count = std::count(tmp.begin(), tmp.end(), ' ');
                    return count > 1;
                });
        } catch (boost::system::system_error& e) {
            status = false;
            std::cout << "Connection refused" << std::endl;
            std::cout << e.code() << std::endl;
            return result;
        }
        result = std::string(this->buffer);
        return result;
    }
};

#endif  // TABLEOFLIFE_TABLEOFLIFE_CLIENT_CLIENT_H
