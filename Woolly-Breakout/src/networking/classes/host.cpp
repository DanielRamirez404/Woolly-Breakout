#include "host.h"

GameHost::MessageHandler GameHost::getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition) {
    return MessageHandler{
        std::thread{ [&]() {
            while (getLoopCondition())
                handleMessage(socket.read());     
        }},

        std::thread{ [&]() {
            while (getLoopCondition())
                socket.send(getOutput());
        }}
    };
}