#pragma once
#include "host.h"
#include "../include-asio.h"
#include <string_view>

class GameClient : public GameHost {
    public:

        void connectTo(std::string_view serverAddress, int serverPort);

    private:

        asio::ip::tcp::resolver resolver{ context };
};