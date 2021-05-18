#include <boost/asio/io_service.hpp>
#include "Server/Server.h"
#include <iostream>


int main() {
    Server ser = Server();
    ser.SetUp();
    try {
        boost::asio::io_service io_service;
        Server s;
        io_service.run();
    }
    catch (std::exception& e)
        std::cerr << "Exception: " << e.what() << "\n";
    ser.ShutDown();
    return 0;
}