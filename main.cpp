#include "Server/Server.h"
#include <boost/log/trivial.hpp>

int main() {
    Server ser = Server();
    ser.SetUp();

    ser.ShutDown();
    return 0;
}