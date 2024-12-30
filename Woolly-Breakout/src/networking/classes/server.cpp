#include "server.h"
#include "../utilities.h"
#include "../include-asio.h"
#include <system_error>
#include <iostream>
#include <string>
#include <thread>
#include <optional>

GameServer::GameServer(int port) : acceptor { context, asio::ip::tcp::endpoint{{}, 6000} } {
    std::cout << "Initialized Server on port: " + std::to_string(port) << '\n';
}

std::thread GameServer::getAcceptingThread() {
    std::cout << "Running server\n";

    return std::thread{[&]() {
        acceptClient(client);
        client.send("hello, client!\n");
    }};
}

MessageHandler GameServer::getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition) {
    return getMessageHandler(client, handleMessage, getOutput, getLoopCondition);
}

void GameServer::acceptClient(Socket& socket) {
    acceptor.accept(socket.get());
    std::cout << "Established connection from client: " << socket << '\n';
}

int main(int argc, char *argv[]) {

    tryNetworkingFunction([]() {

        GameServer server{6000};
        server.getAcceptingThread().join();

        auto threads{
            server.getMessageThreads(
                [](std::string message) {
                    std::cout << message;
                },

                []() {
                    static int count{0};
                    ++count;

                    if (count <= 3)
                        return std::optional<std::string>{"hello, client!\n"};
                    
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