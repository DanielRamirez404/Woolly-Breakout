#include "utilities.h"
#include "include-asio.h"
#include <functional>
#include <stdexcept>
#include <system_error>
#include <string>
#include <array>

void tryNetworkingFunction(const std::function<void()>& function) {
    try{
        function();
    } catch(const std::error_code& error) {
        throw std::runtime_error{"Failed networking function. System error [" + std::to_string(error.value()) + "]: " + error.message() };
    }
}

void readFromSocket(asio::ip::tcp::socket& socket) {
    std::array<char, 128> buffer{};

    std::error_code error{};
            
    size_t length{ socket.read_some(asio::buffer(buffer), error) };

    if (error == asio::error::eof)
        return;

    if (error) 
        throw error;
            
    std::cout.write(buffer.data(), length); 
}

void writeToSocket(asio::ip::tcp::socket& socket, std::string_view message) {
    std::error_code error{};
    asio::write(socket, asio::buffer(message), error);
}

std::ostream& operator<<(std::ostream &out, const asio::ip::tcp::socket& socket) {
    out << socket.remote_endpoint().address().to_string() << ':'
        << socket.remote_endpoint().port();

    return out;
}