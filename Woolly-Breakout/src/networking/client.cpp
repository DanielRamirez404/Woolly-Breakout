#include "utilities.h"
#include "include-asio.h"
#include <iostream>
#include <system_error>
#include <array>

int main(int argc, char *argv[]) {
    
    tryNetworkingFunction([]() {

        asio::io_context context{};
        asio::ip::tcp::resolver resolver{context};

        auto endpoint{resolver.resolve("127.0.0.1", "6000")};

        asio::ip::tcp::socket socket{ context };

        asio::connect(socket, endpoint);

        std::cout << "connected to server\n";

        while (true) {
            std::array<char, 128> buffer{};

            std::error_code error{};
            
            size_t length{ socket.read_some(asio::buffer(buffer), error) };

            if (error == asio::error::eof)
                break;

            if (error) 
                throw error;
            
            std::cout.write(buffer.data(), length); 
        }
    });

    return 0;
}