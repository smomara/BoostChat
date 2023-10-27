#pragma once

#include <functional>
#include <optional>
#include <unordered_set>

#include <boost/asio.hpp>

#include "tcp_connection.h"

namespace BoostChat{
    namespace io = boost::asio;
    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
        using OnJoinHandler = std::function<void(TCPConnection::pointer)>;
        using OnLeaveHandler = std::function<void(TCPConnection::pointer)>;
        using OnClientMessageHandler = std::function<void(std::string)>;

    public:
        TCPServer(IPV ipv, int port);

        int Run();
        void Broadcast(const std::string& message);

    private:
        void startAccept();

    public:
        OnJoinHandler OnJoin;
        OnLeaveHandler OnLeave;
        OnClientMessageHandler OnClientMessage;

    private:
        IPV _ipVersion;
        int _port;

        io::io_context _ioContext;
        io::ip::tcp::acceptor _acceptor;
        std::optional<io::ip::tcp::socket> _socket;
        std::unordered_set<TCPConnection::pointer> _connections {};
    };
}