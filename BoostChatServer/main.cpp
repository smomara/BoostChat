#include <iostream>

#include "BoostChatNetwork/server/tcp_server.h"

int main(int argc, char* argv[]) {
    BoostChat::TCPServer server {BoostChat::IPV::V4, 1337};

    server.OnJoin = [](BoostChat::TCPConnection::pointer server) {
        std::cout << "User has joined the server: " << server->GetUsername() << std::endl;
    };

    server.OnLeave = [](BoostChat::TCPConnection::pointer server) {
        std::cout << "User has left the server: " << server->GetUsername() << std::endl;
    };

    server.OnClientMessage = [&server](const std::string& message) {
        // Parse the message
        // Do game server things

        // Send message to client
        server.Broadcast(message);
    };

    server.Run();

    return 0;
}