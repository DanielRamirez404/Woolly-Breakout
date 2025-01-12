#pragma once
#include "host.h"
#include "../include-asio.h"
#include <thread>
#include <string>

class GameServer : public GameHost {
    public:
        
        GameServer(int port);
        
        std::thread getAcceptingThread();         
        void broadcast(std::string message);

    private:

        asio::ip::tcp::acceptor acceptor;
        
        void acceptClient(Socket& client);
};