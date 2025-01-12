#include "client.h"
#include "../include-asio.h"
#include <iostream>
#include <string>
#include <string_view>

void GameClient::connectTo(std::string_view serverAddress, int serverPort) {
    auto endpoint{ resolver.resolve(serverAddress.data(), std::to_string(serverPort)) };
    asio::connect(socket.get(), endpoint);
    std::cout << "Connected to server: " << socket << '\n';
}