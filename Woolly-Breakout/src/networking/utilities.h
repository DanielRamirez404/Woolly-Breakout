#pragma once
#include "include-asio.h"
#include <functional>
#include <iostream>
#include <string_view>

void tryNetworkingFunction(const std::function<void()>& function);
void readFromSocket(asio::ip::tcp::socket& socket);
void writeToSocket(asio::ip::tcp::socket& socket, std::string_view message);
std::ostream& operator<<(std::ostream &out, const asio::ip::tcp::socket& socket);