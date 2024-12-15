#pragma once
#include "map.h"
#include "SDL.h"
#include <memory>
#include <functional>
#include <string_view>

class GameWindow {
	public:

		GameWindow();
        void startGameLoop(const std::function<void(SDL_Event&)>& eventLogic, const Map& map);

	private:
		
		struct deleter {
  			void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  			void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  			void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
			void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
		};

		std::unique_ptr<SDL_Window, deleter> window{ nullptr };
		std::unique_ptr<SDL_Renderer, deleter> renderer{ nullptr };

		std::unique_ptr<SDL_Texture, deleter> wallTexture{ nullptr };
		std::unique_ptr<SDL_Texture, deleter> grassTexture{ nullptr };
		std::unique_ptr<SDL_Texture, deleter> playerTextre{ nullptr };

		void initializeLibraries();
        void allocateUIResources();
        void allocateImages();

		SDL_Texture* loadImage(std::string_view path);
		void renderMap(const Map& map);
};
