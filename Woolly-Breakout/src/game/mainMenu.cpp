#include "mainMenu.h"
#include "ui/menuWindow.h"
#include "../constants/constants.h"
#include "game.h"

void MainMenu::start() {
    startMainMenu();
}

void MainMenu::startMainMenu() {
    MenuWindow mainMenu{};

    mainMenu.addTexture(
        "logo", 
        Constants::Window::halfSize * 0.7,
        Constants::Window::largePadding * 0.65,
        Constants::Window::largePadding * 1.25,
        Constants::Window::largePadding * 1.25
    );

    mainMenu.addButton(
        "play",
        MenuWindow::Button { 
            int(Constants::Window::halfSize * 0.66),
            int(Constants::Window::halfSize),
            int(Constants::Window::largePadding * 1.35),
            int(Constants::Window::bigPadding * 1.2),
            [&]() { startPlayMenu(); }
        }
    );
    
    mainMenu.run();
}

void MainMenu::startPlayMenu() {
    MenuWindow playMenu{};

    constexpr int horizontalPadding{ int(Constants::Window::halfSize * 0.7) };
    constexpr int verticalPadding{ int(Constants::Window::largePadding * 0.75) };
    constexpr int width{int(Constants::Window::largePadding * 1.2 )};
    constexpr int length{int(Constants::Window::bigPadding * 1.2 )};

    constexpr int buttonsPadding{ int(Constants::Window::bigPadding * 1.65) };

    playMenu.addButton("solo", MenuWindow::Button{ horizontalPadding, verticalPadding, width, length, [&]() { 
        Game soloGame{};
        soloGame.run(); 
        startMainMenu();
    }});

    playMenu.addButton("host", MenuWindow::Button{ horizontalPadding, verticalPadding + buttonsPadding, width, length, [&]() { 
        Game lanGame{"host"};
        lanGame.run(); 
        startMainMenu();
    }});
    
    playMenu.addButton("join", MenuWindow::Button{ horizontalPadding, verticalPadding + buttonsPadding * 2, width, length, [&]() { 
        Game lanGame{"127.0.0.1"};
        lanGame.run(); 
        startMainMenu();
    }});
    
    playMenu.run();
}
