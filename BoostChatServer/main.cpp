#include <iostream>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        // make an io_context
        // context object that boost uses to keep information on I/O for system
        boost::asio::io_context io_context;

        // make an acceptor
        // acceptor object that accepts connections
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));

        while(true) {
            // use the acceptor to wait for a connection
            // store the connection in the socket
            std::cout << "Accepting connections on port 1337!\n";
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // once you have a connection, write to the socket
            std::cout << "Client connected! Sending message!\n";
            std::string hello_message = "Hello, Client!\n";
            boost::system::error_code error;

            boost::asio::write(socket, boost::asio::buffer(hello_message), error);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
