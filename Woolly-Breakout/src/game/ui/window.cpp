#include "window.h"
#include "elements.h"
#include "renderer.h"
#include "../../constants/constants.h"
#include "../../constants/notation.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>

Smart::Window Window::window = nullptr;
Renderer Window::renderer = Renderer();
bool Window::isSDLInitialized = false;

Window::Window() {
	if (isSDLInitialized)
        return;

    initializeLibraries();
    allocateUIResources();
}

void Window::initializeLibraries() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("SDL_Image Initialization Error");	
}

void Window::allocateUIResources() {
    window.reset(SDL_CreateWindow("Woolly Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::Window::size, Constants::Window::size, SDL_WINDOW_SHOWN));

	if (!window)
		throw std::runtime_error("Window Initialization Error");
	
	renderer.setRenderer(window.get());
	
	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");   

    renderer.setTransparentMode();

	constexpr std::string_view extraNames[] { "player", "frame" };

	for (std::string_view name : extraNames)
		renderer.loadTexture(name.data());

	for (auto const& [name, character] : Notation::characters)
		renderer.loadTexture(name.data());
}
