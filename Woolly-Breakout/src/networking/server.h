#pragma once
#include "utilities.h"
#include "include-asio.h"
#include "socket.h"
#include <thread>

class GameServer {
    public:
        
        GameServer(int port);
        std::thread getAcceptingThread();         
        MessageHandler getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition);

    private:

        asio::io_context context{};
        asio::ip::tcp::acceptor acceptor;
        Socket client{context};

        void acceptClient(Socket& socket);
        void handleClient(Socket& socket);
        
};