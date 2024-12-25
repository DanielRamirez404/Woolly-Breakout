#include "notation.h"
#include <unordered_map>
#include <string_view>

std::unordered_map<std::string_view, char> Notation::characters { 
    {"grass", '0'},
    {"wall", '1'},
    {"door", '2'},
    {"key", '3'}
};