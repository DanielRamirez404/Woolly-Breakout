#pragma once
#include "include-asio.h"
#include "socket.h"

class GameServer {
    public:
        
        GameServer(int port);
        void run();

    private:

        asio::io_context context{};
        asio::ip::tcp::acceptor acceptor;
        Socket client{context};

        void acceptClient(Socket& socket);
        void handleClient(Socket& socket);
};