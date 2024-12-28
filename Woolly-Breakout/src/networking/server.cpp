#include "server.h"
#include "utilities.h"
#include "include-asio.h"
#include <system_error>
#include <iostream>
#include <string>

GameServer::GameServer(int port) : acceptor{context, asio::ip::tcp::endpoint{{}, 6000}} {
    std::cout << "Initialized Server on port: " + std::to_string(port) << '\n';
}

void GameServer::run() {
    std::cout << "Running server\n";
    acceptClient(client);

    //this won't stay on the final version
    std::error_code error{};
    asio::write(client, asio::buffer("hello, client!\n"), error);

    while (true) {
        handleClient(client);
    }
}

void GameServer::acceptClient(asio::ip::tcp::socket& socket) {
    acceptor.accept(socket);
    std::cout << "Established connection from client: " << socket << '\n';
}

void GameServer::handleClient(asio::ip::tcp::socket& socket) {
    //todo
}

int main(int argc, char *argv[]) {

    tryNetworkingFunction([]() {
        GameServer server{6000};
        server.run();
    });

    return 0;
}