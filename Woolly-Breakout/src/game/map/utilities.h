#pragma once
#include <string>

template <typename T>
struct Coordinates {
	T i{};
	T j{};

	std::string toString() const {
		return std::to_string(i).append(",").append(std::to_string(j));
	}

	void read(std::string& string) {
		bool isFloat{ string.find('.') != std::string::npos };

		int commaIndex{ static_cast<int>(string.find(',')) };

		auto i_string{ string.substr(0, commaIndex) };
		auto j_string{ string.substr(commaIndex + 1, string.size() - commaIndex	- 1) };

		if (isFloat) {
			i = static_cast<T>(std::stof(i_string));
			j = static_cast<T>(std::stof(j_string));
		} else {
			i = static_cast<T>(std::stoi(i_string));
			j = static_cast<T>(std::stoi(j_string));
		}
	};

	Coordinates<T>() {};
	Coordinates<T>(T i_coordinate, T j_coordinate) : i{i_coordinate}, j{j_coordinate} {}
	Coordinates<T>(std::string& string) { read(string); }

	Coordinates<int> toInt() const {
		return { static_cast<int>(i), static_cast<int>(j) };
	}

	Coordinates<float> toFloat() const {
		return { static_cast<float>(i), static_cast<float>(j) };
	}

	bool operator==(Coordinates<T>const& coordinates) const {
		return coordinates.i == i && coordinates.j == j;
	}
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};