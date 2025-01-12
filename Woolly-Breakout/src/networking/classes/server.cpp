#include "server.h"
#include "../utilities.h"
#include "../include-asio.h"
#include <iostream>
#include <string>
#include <thread>
#include <utility>

GameServer::GameServer(int port) : acceptor { context, asio::ip::tcp::endpoint{{}, 6000} } {
    std::cout << "Initialized Server on port: " + std::to_string(port) << '\n';
}

std::thread GameServer::getAcceptingThread() {
    std::cout << "Running server\n";

    return std::thread{[&]() {
        acceptClient(socket);
    }};
}

void GameServer::acceptClient(Socket& client) {
    acceptor.accept(client.get());
    std::cout << "Established connection from client: " << client << '\n';
}

void GameServer::broadcast(std::string message) {
    socket.send(std::move(message));
}
