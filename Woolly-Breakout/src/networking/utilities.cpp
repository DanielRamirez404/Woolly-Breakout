#include "utilities.h"
#include "classes/socket.h"
#include <functional>
#include <stdexcept>
#include <system_error>
#include <string>
#include <thread>

void tryNetworkingFunction(const std::function<void()>& function) {
    try{
        function();
    } catch(const std::error_code& error) {
        throw std::runtime_error{"Failed networking function. System error [" + std::to_string(error.value()) + "]: " + error.message() };
    }
}

MessageHandler getMessageHandler(Socket& socket, const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition) {
    return MessageHandler{
        std::thread{ [&]() {
            while (getLoopCondition())
                handleMessage(socket.read());     
        }},

        std::thread{ [&]() {
            while (getLoopCondition()) {
                auto message{ getOutput() };

                if (message) 
                    socket.send(message.value());
            }
        }}
    };
}