#pragma once
#include <unordered_map>
#include <string_view>

enum NetworkEvent {
	GetMap,
	SetPlayer,
};

struct Notation {
    static std::unordered_map<std::string_view, char> characters;
	static std::unordered_map<NetworkEvent, char> networkCharacters;
};