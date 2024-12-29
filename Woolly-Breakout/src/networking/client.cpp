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

void GameClient::connectTo(std::string_view serverAddress, int serverPort) {
    auto endpoint{ resolver.resolve(serverAddress.data(), std::to_string(serverPort)) };
    asio::connect(server, endpoint);
    std::cout << "Connected to server: " << server << '\n';
}

void GameClient::handleConnection(const std::function<void(std::string_view)>& handleMessage, const std::function<std::optional<std::string>()>& getInput) {   
    
    std::thread messageHandler { [&]() {
        while (true) {
            auto message{ readFromSocket(server) };
            
            if (message)
                handleMessage(message.value());
        }     
    }};

    std::thread inputHandler{ [&]() {
        while (true) {
            auto input{ getInput() };

            if (input) 
                writeToSocket(server, input.value());
        }
    }};

    messageHandler.join();
    inputHandler.join();
}

int main(int argc, char *argv[]) {
    
    tryNetworkingFunction([]() {
        GameClient client{};
        client.connectTo("127.0.0.1", 6000);
        client.handleConnection(
            [](std::string_view message) {
                std::cout << message;
            },

            []() {
                static int count{0};
                ++count;

                if (count <= 3)
                    return std::optional<std::string>{"hello, server!\n"};
                
                return std::optional<std::string>{std::nullopt};
            }
        );    
    });

    return 0;
}