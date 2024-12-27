#include <iostream>
#include <system_error>
#include <array>

#ifndef ASIO_STANDALONE
    #define ASIO_STANDALONE
#endif

#include <asio.hpp>

int main(int argc, char *argv[]) {
    
    
    try {

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

    } catch (const std::error_code& error) {
        std::cerr << error.value() << '\n';
    }



    return 0;
}