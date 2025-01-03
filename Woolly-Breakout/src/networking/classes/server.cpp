#include "server.h"
#include "../utilities.h"
#include "../include-asio.h"
#include <system_error>
#include <iostream>
#include <string>
#include <thread>
#include <optional>
#include <utility>

GameServer::GameServer(int port) : acceptor { context, asio::ip::tcp::endpoint{{}, 6000} } {
    std::cout << "Initialized Server on port: " + std::to_string(port) << '\n';
}

std::thread GameServer::getAcceptingThread() {
    std::cout << "Running server\n";

    return std::thread{[&]() {
        acceptClient(client);
    }};
}

MessageHandler GameServer::getMessageThreads(const InputHandler& handleMessage, const OutputGetter& getOutput, const LoopEnder& getLoopCondition) {
    return getMessageHandler(client, handleMessage, getOutput, getLoopCondition);
}

void GameServer::acceptClient(Socket& socket) {
    acceptor.accept(socket.get());
    std::cout << "Established connection from client: " << socket << '\n';
}

void GameServer::broadcast(std::string message) {
    client.send(std::move(message));
}
