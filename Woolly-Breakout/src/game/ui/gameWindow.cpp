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
#include <string>
#include <string_view>
#include <ranges>
#include <thread>

GameWindow::GameWindow(bool isMultiplayer, bool isFirstPlayers) 
	: isMultiplayerGame{ isMultiplayer }, isFirstPlayerPerspective{ isFirstPlayers } 
{
	initializeLibraries();
    allocateUIResources();
}

void GameWindow::startGameLoop(const Map& map, const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const std::function<bool()>& endCondition) {
    SDL::Event event{};
    constexpr int delayTime{ 1000 / Constants::Frames::fps };
		
	renderMap(map);

    while (true) {

		if (loopLogic)
			loopLogic();

		if (endCondition())
			return;
        
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
	addPlayersToRenderer(map);
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

	const auto& player { (isFirstPlayerPerspective) ? map.getPlayer() : map.getSecondPlayer() };

	const Coordinates<float>& coordinates{ player.getCoordinates() };
	const Coordinates<int> roundedCoordinates{ player.getRoundedCoordinates() };

	constexpr int tilesToCenter{ Constants::Map::TileRendering::center - 1 };

	const int min_i{ roundedCoordinates.i - tilesToCenter };
	const int max_i{ roundedCoordinates.i + tilesToCenter + 1 };
	const int min_j{ roundedCoordinates.j - tilesToCenter };
	const int max_j{ roundedCoordinates.j + tilesToCenter + 1 };

	auto increaseBoth{ [&](int& first, int&second) {  
		++first;
		++second;
	}};

	const float i_off_constant{ coordinates.i - static_cast<float>(roundedCoordinates.i) };
	const float j_off_constant{ coordinates.j - static_cast<float>(roundedCoordinates.j) };

	for (int i{min_i}, i_count{0}; i <= max_i; increaseBoth(i, i_count))
		for (int j{min_j}, j_count{0}; j <= max_j; increaseBoth(j, j_count)) {

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

	std::string name{};

	for (const auto& [string, character] : Notation::characters)
		if (tile == character)
			name = string;

	renderer.addTexture(name);
}

void GameWindow::addPlayersToRenderer(const Map& map) {
	renderer.setArea(Constants::Map::TileRendering::players, Constants::Map::TileRendering::size);
	renderer.addTexture("player");

	if (isMultiplayerGame) {
		const Coordinates<float>& player{ ((isFirstPlayerPerspective) ? map.getPlayer() : map.getSecondPlayer()).getCoordinates() };
		const Coordinates<float>& teammate{ ((!isFirstPlayerPerspective) ? map.getPlayer() : map.getSecondPlayer()).getCoordinates() };
		
		Coordinates<float> relativeCoordinates{ teammate.i - player.i, teammate.j - player.j };
		relativeCoordinates.i *= Constants::Map::TileRendering::size;
		relativeCoordinates.j *= Constants::Map::TileRendering::size;
		const Coordinates<int> printableCoordinates{ Constants::Map::TileRendering::players + static_cast<int>(relativeCoordinates.i), Constants::Map::TileRendering::players + static_cast<int>(relativeCoordinates.j) };

		renderer.setArea(printableCoordinates.j, printableCoordinates.i, Constants::Map::TileRendering::size);
		renderer.addTexture("player");
	}
}
