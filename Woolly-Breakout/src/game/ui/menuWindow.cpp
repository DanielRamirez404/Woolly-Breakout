#include "menuWindow.h"
#include "elements.h"
#include "window.h"
#include "../../constants/constants.h"
#include "SDL.h"
#include <string>
#include <algorithm>

MenuWindow::MenuWindow() : Window() {
	renderer.clear();
    renderer.setArea(0, Constants::Window::size);
    renderer.addTexture("menu-bg");
}

void MenuWindow::addButton(const std::string& texture, MenuWindow::Button button) {
    renderer.setArea(button.x, button.y, button.width, button.length);
    renderer.addTexture(texture + std::string{"-btn"}); 
    buttons.push_back(button);
}

void MenuWindow::run() {
    SDL::Event event{};
		
	renderer.render();
    
    bool hasUserClicked{ false };
    Button* clickedButton{ nullptr };

    while (true) {
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
				return;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) 
                    clickedButton = getClickedButton(event.button.x, event.button.y);
            }
            else if (event.type == SDL_MOUSEBUTTONUP) {
                if (clickedButton)
                    clickedButton->onClick();
            }
        }
    }
}

MenuWindow::Button* MenuWindow::getClickedButton(int x, int y) {
   auto foundButton { std::find_if(buttons.begin(), buttons.end(), [&](Button& button) {
        return button.includes(x, y);
    })}; 

    return (foundButton != buttons.end()) ? &*foundButton : nullptr;
}

