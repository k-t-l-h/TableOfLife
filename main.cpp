#include "Server/Server.h"

int main() {
    Server ser = Server();
    ser.SetUp();

    ser.ShutDown();
    return 0;
}