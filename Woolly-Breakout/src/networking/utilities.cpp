#include "utilities.h"
#include "include-asio.h"
#include <functional>
#include <stdexcept>
#include <system_error>
#include <string>
#include <array>
#include <optional>

void tryNetworkingFunction(const std::function<void()>& function) {
    try{
        function();
    } catch(const std::error_code& error) {
        throw std::runtime_error{"Failed networking function. System error [" + std::to_string(error.value()) + "]: " + error.message() };
    }
}