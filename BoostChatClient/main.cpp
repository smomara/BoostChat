#include <BoostChatNetwork/client/tcp_client.h>

#include <iostream>
#include <thread>

int main(int argc, char* argv[]) {
    BoostChat::TCPClient client {"localhost", 1337};

    client.OnMessage = [](const std::string& message) {
        std::cout << message;
    };

    std::thread t{ [&client] () { client.Run(); }};

    while (true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);
    }

    client.Stop();
    t.join();
    return 0;
}