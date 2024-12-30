#pragma once
#include "include-asio.h"
#include "utilities.h"
#include "socket.h"
#include <string_view>
#include <optional>
#include <utility>
#include <thread>

class GameClient {
    public:

        void connectTo(std::string_view serverAddress, int serverPort);
        MessageHandler getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition);

    private:

        asio::io_context context{};
        asio::ip::tcp::resolver resolver{ context };
        Socket server{ context };

};