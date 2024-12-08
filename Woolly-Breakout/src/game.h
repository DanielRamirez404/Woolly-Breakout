#pragma once
#include "map.h"
#include "SDL.h"
#include <memory>
#include <string_view>

class Game {
	public:

		Game();
		
		void initializeLibraries();
		void run();

	private:

		
		struct deleter {
  			void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  			void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  			void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
			void operator()(SDL_Surface *p) const { SDL_FreeSurface; }
		};

		std::unique_ptr<SDL_Window, deleter> window{ nullptr };
		std::unique_ptr<SDL_Renderer, deleter> renderer{ nullptr };

		std::unique_ptr<SDL_Texture, deleter> wallTexture{ nullptr };
		std::unique_ptr<SDL_Texture, deleter> grassTexture{ nullptr };

		Map map{};

		void loadResources();
		SDL_Texture* loadImage(std::string_view path);
		void renderMap();
};
