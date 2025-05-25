#include "game/mainMenu.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {

	try {
        MainMenu mainMenu{};
        mainMenu.start();
	} catch(const std::runtime_error& error) {
		std::cerr << "Runtime error: " << error.what() << ".\n";
	} catch(...) {
		std::cerr << "An unexpected unsolvable error has occurred.\n";
	}
	
	return 0;
}
