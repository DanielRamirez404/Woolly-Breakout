#include "game/game.h"
#include <stdexcept>
#include <iostream>

int main(int argc, char *argv[]) {

	try {
		Game myGame{};
		myGame.run();
	} catch(const std::runtime_error& error) {
		std::cerr << "Runtime error: " << error.what() << ".\n";
	} catch(...) {
		std::cerr << "An unexpected unsolvable error has occurred.\n";
	}
	
	return 0;
}