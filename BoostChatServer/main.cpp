#include <iostream>

#include <BoostChatNetwork/tcp_server.h>

int main(int argc, char* argv[]) {
    BoostChat::TCPServer server {BoostChat::IPV::V4, 1337};

    server.Run();

    return 0;
}