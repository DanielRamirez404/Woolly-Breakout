#include "renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <string_view>
#include <stdexcept>

void Renderer::setRenderer(SDL::Window* window) {
    renderer.reset(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
}

void Renderer::setArea(int x, int y, int width, int height) {
	area = { x, y, width, height };
}

void Renderer::setArea(int x, int y, int size) {
	area = { x, y, size, size };
}

void Renderer::loadTexture(const std::string& name) {	
    std::string path{"../../res/" + name + ".png"};
	
	Smart::Surface temp{ IMG_Load(path.data()) };

	if (!temp)
		throw std::runtime_error{"Can\'t load image from path: " + path};

	SDL::Texture* texture{ SDL_CreateTextureFromSurface(renderer.get(), temp.get()) };

	if (!texture)
		throw std::runtime_error{"Can\'t create image texture from path: " + path};

	textures.emplace(name, texture);
}

void Renderer::setTransparentMode() {
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
}

void Renderer::addColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
	SDL_RenderFillRect(renderer.get(), &area);
}

void Renderer::addTexture(const std::string& name) {
	SDL_RenderCopy(renderer.get(), textures[name].get(), nullptr, &area);
}

void Renderer::clear() {
	SDL_RenderClear(renderer.get());
}

void Renderer::render() {
	SDL_RenderPresent(renderer.get());
}

Renderer::operator bool() const {
	return bool(renderer);
}