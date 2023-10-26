#include "BoostChatNetwork/tcp_connection.h"

#include <iostream>

namespace BoostChat {
    BoostChat::TCPConnection::TCPConnection(boost::asio::io_context &ioContext) : _socket(ioContext) {

    }

    void BoostChat::TCPConnection::Start() {
        auto strongThis = shared_from_this();

        boost::asio::async_write(_socket, boost::asio::buffer(_message),
                                 [strongThis](const boost::system::error_code& error, size_t bytesTransferred) {
            if (error) {
                std::cout << "Failed to send message!\n";
            } else {
                std::cout << "Sent " << bytesTransferred << " bytes of data!\n";
            }
        });
    }
}