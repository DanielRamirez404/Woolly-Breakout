#include <iostream>

#ifndef ASIO_STANDALONE
    #define ASIO_STANDALONE
#endif

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

int main(int argc, char *argv[]) {
    std::cout << "Compiled!\n";
    return 0;
}