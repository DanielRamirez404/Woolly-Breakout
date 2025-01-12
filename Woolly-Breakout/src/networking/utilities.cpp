#include "utilities.h"
#include <functional>
#include <stdexcept>
#include <system_error>
#include <string>

void tryNetworkingFunction(const std::function<void()>& function) {
    try {
        function();
    } catch(const std::error_code& error) {
        throw std::runtime_error{"Failed networking function. System error [" + std::to_string(error.value()) + "]: " + error.message() };
    }
}