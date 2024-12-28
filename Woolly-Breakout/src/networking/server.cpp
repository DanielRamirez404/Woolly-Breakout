#include "utilities.h"
#include "include-asio.h"
#include <iostream>
#include <system_error>

int main(int argc, char *argv[]) {

    tryNetworkingFunction([]() {
        asio::io_context context{};
        asio::ip::tcp::acceptor acceptor{context, asio::ip::tcp::endpoint{asio::ip::tcp::v4(), 6000}};
        asio::ip::tcp::socket socket{ context };
        acceptor.accept(socket);

        std::cout << "establishing connection from client: "
                << socket.remote_endpoint().address().to_string() << ':'
                << socket.remote_endpoint().port() << '\n';

        std::error_code error{};
        asio::write(socket, asio::buffer("hello, world!\n"), error);

        while (true);
    });

    return 0;
}