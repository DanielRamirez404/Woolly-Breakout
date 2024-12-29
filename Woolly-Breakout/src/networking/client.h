#pragma once
#include "include-asio.h"
#include "socket.h"
#include <string_view>
#include <optional>

class GameClient {
    public:

        void connectTo(std::string_view serverAddress, int serverPort);
        void handleConnection(const std::function<void(std::string_view)>& handleMessage, const std::function<std::optional<std::string>()>& getInput);

    private:

        asio::io_context context{};
        asio::ip::tcp::resolver resolver{ context };
        Socket server{ context };

};