#include "gameWindow.h"
#include "elements.h"
#include "../../constants/constants.h"
#include "../../constants/notation.h"
#include "../map/utilities.h"
#include "../entities/safe-zone.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <functional>
#include <string_view>
#include <ranges>

GameWindow::GameWindow() {
	initializeLibraries();
    allocateUIResources();
}

void GameWindow::startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map) {
    SDL::Event event{};
    constexpr int delayTime{ 1000 / Constants::Frames::fps };
		
	renderMap(map);

    while (true) {

		loopLogic();
        
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
				return;

            eventLogic(event);
        }

		SDL_Delay(delayTime);
		renderMap(map);
    }
}

void GameWindow::initializeLibraries() {
	
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("SDL_Image Initialization Error");	
}

void GameWindow::allocateUIResources() {
    window.reset(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::Window::size, Constants::Window::size, SDL_WINDOW_SHOWN));

	if (!window)
		throw std::runtime_error("Window Initialization Error");
	
	renderer.setRenderer(window.get());
	
	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");   

    renderer.setTransparentMode();

	constexpr std::string_view extraNames[] { "player", "frame" };

	for (std::string_view name : extraNames)
		renderer.loadTexture(name.data());

	for (auto const& [name, character] : Notation::characters) {
		renderer.loadTexture(name.data());
	}
}

void GameWindow::renderMap(const Map& map) {
	renderer.clear();

	addMapToRenderer(map);
	addPlayerToRenderer(map);
	addStatusToRenderer(map);

	renderer.render();
}

void GameWindow::addStatusToRenderer(const Map& map) {
	renderer.setArea(0, 0, Constants::Window::size, Constants::StatusBar::length);
	renderer.addColor(0, 0, 0, 255);

	int pickedKeys{ map.getPickedUpKeys() };

	for (int i{0}; i < Constants::SafeZone::totalKeys; ++i) {

		renderer.setArea(Constants::StatusBar::Frame::padding + Constants::StatusBar::Frame::size * i, Constants::StatusBar::Frame::padding, Constants::StatusBar::Frame::size);
		renderer.addTexture("frame");
		
		if (i < pickedKeys)
			renderer.addTexture("key");
	}
}

void GameWindow::addMapToRenderer(const Map& map) {

	const Coordinates<float>& player{ map.getPlayer().getCoordinates() };
	const Coordinates<int> roundedPlayer{ map.getPlayer().getRoundedCoordinates() };

	constexpr int tilesToCenter{ Constants::Map::TileRendering::center - 1 };

	const int min_i{ roundedPlayer.i - tilesToCenter };
	const int max_i{ roundedPlayer.i + tilesToCenter + 1 };
	const int min_j{ roundedPlayer.j - tilesToCenter };
	const int max_j{ roundedPlayer.j + tilesToCenter + 1 };

	auto increase_i{ [&](int& i, int&i_count) {  
		++i;
		++i_count;
	}};

	auto increase_j{ [&](int& j, int&j_count) {  
		++j;
		++j_count;
	}};

	const float i_off_constant{ player.i - static_cast<float>(roundedPlayer.i) };
	const float j_off_constant{ player.j - static_cast<float>(roundedPlayer.j)};

	for (int i{min_i}, i_count{0}; i <= max_i; increase_i(i, i_count))
		for (int j{min_j}, j_count{0}; j <= max_j; increase_j(j, j_count)) {

			if (i < 0 || j < 0 || i >= Constants::Map::Matrix::size || j >= Constants::Map::Matrix::size)
				continue;

			renderer.setArea((j_count - j_off_constant) * Constants::Map::TileRendering::size, (i_count - i_off_constant) * Constants::Map::TileRendering::size, Constants::Map::TileRendering::size);
			addTileToRenderer(map(i, j));
		}
}

void GameWindow::addTileToRenderer(char tile) {
	if (tile == Notation::characters["wall"]) {
		renderer.addTexture("wall");
		return;
	}

	renderer.addTexture("grass");

	if (tile == Notation::characters["grass"])
		return;

	const auto& name{ (tile == Notation::characters["door"]) ? "door" : "key" };
	renderer.addTexture(name);
}

void GameWindow::addPlayerToRenderer(const Map& map) {
	const Coordinates<float>& player{ map.getPlayer().getCoordinates() };
	renderer.setArea(Constants::Map::TileRendering::players, Constants::Map::TileRendering::players, Constants::Map::TileRendering::size);
	renderer.addTexture("player");
}
