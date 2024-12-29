#include "socket.h"
#include "include-asio.h"
#include <string>
#include <optional>
#include <iostream>
#include <algorithm>
#include <utility>

Socket::Socket(asio::io_context& context) : socket{ context } {}

std::string Socket::read(char terminatingCharacter) {
    std::string message{ readOnce(terminatingCharacter) };

    while (message.empty() || message.back() != terminatingCharacter)
        message.append( readOnce(terminatingCharacter) );

    return message.substr(0, message.size() - 1);
}

void Socket::send(std::string message, char terminatingCharacter) {
    message += terminatingCharacter;
    std::error_code error{};
    asio::write(socket, asio::buffer(message), error);
}

std::string Socket::readOnce(char terminatingCharacter) {        
    if (!isBufferEmpty)
        return getMessageFromBuffer(terminatingCharacter);

    std::error_code error{};
    std::array<char, 128> readingArray{};

    socket.read_some(asio::buffer(readingArray), error);

    if (error == asio::error::eof)
        return "";

    if (error) 
        throw error;

    buffer = { readingArray.begin(), readingArray.end() };
    return getMessageFromBuffer(terminatingCharacter);
}

std::string Socket::getMessageFromBuffer(char terminatingCharacter) {
    std::cout.flush();  //it won't work otherwise

    std::size_t charIndex{ buffer.find_first_of(terminatingCharacter) };

    isBufferEmpty = true;
    std::string temp{ std::move(buffer) };
    buffer = "";

    if (charIndex == std::string::npos)
        return temp;

    if (charIndex != buffer.size() - 1) {
        isBufferEmpty = false;
        buffer = temp.substr(charIndex + 1, buffer.size() - charIndex + 1);
    }

    return temp.substr(0, charIndex + 1); 
}

asio::ip::tcp::socket& Socket::get() {
    return socket;
}

std::ostream& operator<<(std::ostream &out, const Socket& socket) {
    out << socket.socket.remote_endpoint().address().to_string() << ':'
        << socket.socket.remote_endpoint().port();

    return out;
}
