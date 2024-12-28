#pragma once
#include "include-asio.h"

class GameServer {
    public:
        
        GameServer(int port);
        void run();

    private:

        asio::io_context context{};
        asio::ip::tcp::acceptor acceptor;
        asio::ip::tcp::socket client{ context };

        void acceptClient(asio::ip::tcp::socket& socket);
        void handleClient(asio::ip::tcp::socket& socket);
};