#pragma once
#include "include-asio.h"
#include <string_view>

class GameClient {
    public:

        void connectTo(std::string_view serverAddress, int serverPort);
        void handleConnection();

    private:

        asio::io_context context{};
        asio::ip::tcp::resolver resolver{ context };
        asio::ip::tcp::socket server{ context };

};