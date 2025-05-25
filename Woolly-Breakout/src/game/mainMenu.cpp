#include "mainMenu.h"
#include "ui/menuWindow.h"
#include "game.h"

void MainMenu::start() {
    startMainMenu();
}

void MainMenu::startMainMenu() {
    MenuWindow mainMenu{};

    mainMenu.addButton("play", MenuWindow::Button{ 300, 300, 250, 100, [&]() { 
        startPlayMenu(); 
    }});
    
    mainMenu.run();
}

void MainMenu::startPlayMenu() {
    MenuWindow playMenu{};

    playMenu.addButton("solo", MenuWindow::Button{ 100, 100, 250, 100, [&]() { 
        Game soloGame{};
        soloGame.run(); 
        startMainMenu();
    }});

    playMenu.addButton("host", MenuWindow::Button{ 100, 300, 250, 100, [&]() { 
        Game lanGame{"host"};
        lanGame.run(); 
        startMainMenu();
    }});
    
    playMenu.addButton("join", MenuWindow::Button{ 100, 500, 250, 100, [&]() { 
        Game lanGame{"127.0.0.1"};
        lanGame.run(); 
        startMainMenu();
    }});
    
    playMenu.run();
}
