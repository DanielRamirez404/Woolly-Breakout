#include "client.h"
#include "../utilities.h"
#include "../include-asio.h"
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