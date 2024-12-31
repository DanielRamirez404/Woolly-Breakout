#include "notation.h"
#include <unordered_map>
#include <string_view>

std::unordered_map<std::string_view, char> Notation::characters { 
    {"grass", '0'},
    {"wall", '1'},
    {"door", '2'},
    {"key", '3'}
};

std::unordered_map<NetworkEvent, char> networkCharacters {
    { NetworkEvent::GetMap, 'm' },
    { NetworkEvent::SetPlayer, 'p' }
};
