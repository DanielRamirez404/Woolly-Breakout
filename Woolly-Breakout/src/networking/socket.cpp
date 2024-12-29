#include "socket.h"
#include "include-asio.h"
#include <string>
#include <optional>
#include <iostream>

Socket::Socket(asio::io_context& context) : socket{ context } {}

std::string Socket::read(char terminatingCharacter) {

    std::string message{ readOnce(terminatingCharacter) };

    while (message.empty() || message.back() != terminatingCharacter) {
        //message.append( readOnce(terminatingCharacter) );
    }

    return message;
}

void Socket::send(std::string message, char terminatingCharacter) {
    message += terminatingCharacter;
    std::error_code error{};
    asio::write(socket, asio::buffer(message), error);
}

std::string Socket::readOnce(char terminatingCharacter) {
    std::array<char, 128> buffer{};

    std::error_code error{};
            
    size_t length{ socket.read_some(asio::buffer(buffer), error) };

    if (error == asio::error::eof)
        return "";

    if (error) 
        throw error;

    std::string string{ buffer.begin(), buffer.end() };
    std::size_t charIndex{ string.find_first_of(terminatingCharacter) };

    return (charIndex != std::string::npos) ? string.substr(0, charIndex + 1) : string;  
}

asio::ip::tcp::socket& Socket::get() {
    return socket;
}

std::ostream& operator<<(std::ostream &out, const Socket& socket) {
    out << socket.socket.remote_endpoint().address().to_string() << ':'
        << socket.socket.remote_endpoint().port();

    return out;
}
