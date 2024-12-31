#include "game/game.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {

	try {
		std::string prompt{ (argc == 1) ? "" : argv[1] };
		Game myGame{std::move(prompt)};
		myGame.run();
	} catch(const std::runtime_error& error) {
		std::cerr << "Runtime error: " << error.what() << ".\n";
	} catch(...) {
		std::cerr << "An unexpected unsolvable error has occurred.\n";
	}
	
	return 0;
}