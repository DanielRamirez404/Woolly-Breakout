#pragma once
#include "../include-asio.h"
#include <string>
#include <optional>
#include <iostream>

class Socket{
    public:
        
        Socket(asio::io_context& context);
        
        std::string read(char terminatingCharacter = ':');
        void send(std::string message, char terminatingCharacter = ':');
        asio::ip::tcp::socket& get();

        friend std::ostream& operator<<(std::ostream &out, const Socket& socket);

    private:
        asio::ip::tcp::socket socket;
        std::string buffer{};
        bool isBufferEmpty{ true };

        std::string readOnce(char terminatingCharacter);
        std::string getMessageFromBuffer(char terminatingCharacter);
};