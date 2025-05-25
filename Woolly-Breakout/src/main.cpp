#include "game/game.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <utility>

#include "game/ui/menuWindow.h"

int main(int argc, char *argv[]) {

	try {
		std::string prompt{ (argc == 1) ? "" : argv[1] };
		MenuWindow w{};

        w.addButton("grass", MenuWindow::Button{ 300, 300, 250, 100, [&](){ 
            Game myGame{std::move(prompt)};
            myGame.run(); 
        } });
        
        w.run();

	} catch(const std::runtime_error& error) {
		std::cerr << "Runtime error: " << error.what() << ".\n";
	} catch(...) {
		std::cerr << "An unexpected unsolvable error has occurred.\n";
	}
	
	return 0;
}
