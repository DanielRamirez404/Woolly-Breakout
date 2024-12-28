#pragma once
#include "include-asio.h"
#include <functional>
#include <iostream>

void tryNetworkingFunction(const std::function<void()>& function);
std::ostream& operator<<(std::ostream &out, const asio::ip::tcp::socket& socket);