#include "client.h"
#include "utilities.h"
#include "include-asio.h"
#include <iostream>
#include <system_error>
#include <array>
#include <string>
#include <string_view>

void GameClient::connectTo(std::string_view serverAddress, int serverPort) {
    auto endpoint{ resolver.resolve(serverAddress.data(), std::to_string(serverPort)) };
    asio::connect(server, endpoint);
    std::cout << "Connected to server: " << server << '\n';
}

void GameClient::handleConnection() {   
    //this won't stay on the final version
    writeToSocket(server, "hello, server!\n");
    
    while (true) {
        readFromSocket(server);
    }
}

int main(int argc, char *argv[]) {
    
    tryNetworkingFunction([]() {
        GameClient client{};
        client.connectTo("127.0.0.1", 6000);
        client.handleConnection();    
    });

    return 0;
}