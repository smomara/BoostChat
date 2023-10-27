#include "BoostChatNetwork/server/tcp_connection.h"

#include <iostream>

namespace BoostChat {
    BoostChat::TCPConnection::TCPConnection(io::ip::tcp::socket&& socket) : _socket(std::move(socket)) {
        boost::system::error_code ec;
        std::stringstream name;
        name << _socket.remote_endpoint();

        _username = name.str();
    }

    void BoostChat::TCPConnection::Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler) {
        // Store our handlers
        _messageHandler = std::move(messageHandler);
        _errorHandler = std::move(errorHandler);

        // Start the read loop
        asyncRead();
    }

    void TCPConnection::Post(const std::string &message) {
        bool queueIdle = _outgoingMessages.empty();

        _outgoingMessages.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void TCPConnection::asyncRead() {
        io::async_read_until(_socket, _streamBuf, "\n", [self = shared_from_this()]
        (boost::system::error_code ec, size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        });
    }

    void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            _socket.close();

            _errorHandler();
            return;
        }

        std::stringstream message;
        message << _username << ": " << std::istream(&_streamBuf).rdbuf();
        _streamBuf.consume(bytesTransferred);

        _messageHandler(message.str());
        asyncRead();
    }

    void TCPConnection::asyncWrite() {
        io::async_write(_socket, io::buffer(_outgoingMessages.front()), [self = shared_from_this()]
                (boost::system::error_code ec, size_t bytesTransferred) {
            self->onWrite(ec, bytesTransferred);
        });
    }

    void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            _socket.close();

            _errorHandler();
            return;
        }

        _outgoingMessages.pop();

        if (!_outgoingMessages.empty()) {
            asyncWrite();
        }
    }
}