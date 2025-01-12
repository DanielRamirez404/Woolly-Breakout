#pragma once
#include "socket.h"
#include "../include-asio.h"
#include <thread>
#include <string>
#include <functional>
#include <utility>

class GameHost {
    public:
        
        using MessageHandler = std::pair<std::thread, std::thread>;
        using InputHandler = std::function<void(std::string)>;
        using OutputGetter = std::function<std::string()>;
        using LoopEnder = std::function<bool()>;
        
        MessageHandler getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition);

    protected:

        GameHost() = default;
        
        asio::io_context context{};
        Socket socket{ context };
};