#include <iostream>
#include <array>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context ioContext;

        // create a resolver
        // resolves hostnames and establish a series of connection strings
        tcp::resolver resolver { ioContext };
        auto endpoints = resolver.resolve("127.0.0.1", "1337");

        // create socket and connect to it
        tcp::socket socket{ ioContext };
        boost::asio::connect(socket, endpoints);

        while (true) {
            // listen for messages
            std::array<char, 128> buffer;
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buffer), error);

            if (error == boost::asio::error::eof) {
                // clean connection cut off
                break;
            } else if (error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buffer.data(), len);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
