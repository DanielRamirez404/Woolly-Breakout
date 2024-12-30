#include "client.h"
#include "utilities.h"
#include "include-asio.h"
#include <iostream>
#include <system_error>
#include <array>
#include <string>
#include <string_view>
#include <optional>
#include <thread>
#include <utility>

void GameClient::connectTo(std::string_view serverAddress, int serverPort) {
    auto endpoint{ resolver.resolve(serverAddress.data(), std::to_string(serverPort)) };
    asio::connect(server.get(), endpoint);
    std::cout << "Connected to server: " << server << '\n';
}

MessageHandler GameClient::getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition) {
    return getMessageHandler(server, handleMessage, getOutput, getLoopCondition);
}

int main(int argc, char *argv[]) {
    
    tryNetworkingFunction([]() {
        GameClient client{};
        client.connectTo("127.0.0.1", 6000);
        auto threads { 
            client.getMessageThreads(
                [](std::string message) {
                    std::cout << message;
                },

                []() {
                    static int count{0};
                    ++count;

                    if (count <= 3)
                        return std::optional<std::string>{"hello, server!\n"};
                    
                    return std::optional<std::string>{std::nullopt};
                },

                []() {
                    return true;
                }
            )    
        };

        threads.first.join();
        threads.second.join();
    });

    return 0;
}