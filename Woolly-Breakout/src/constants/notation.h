#pragma once
#include <unordered_map>
#include <string_view>


struct Notation {
    static std::unordered_map<std::string_view, char> characters;
};