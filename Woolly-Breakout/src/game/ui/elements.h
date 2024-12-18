#pragma once
#include "SDL.h"
#include <memory>

namespace SDL
{
    using Window = SDL_Window;
    using Renderer = SDL_Renderer;
    using Texture = SDL_Texture;
    using Surface = SDL_Surface;
    using Event = SDL_Event;
}


namespace Smart
{
    struct Deleter {
        void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
        void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
        void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
        void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
    };

    using Window = std::unique_ptr<SDL::Window, Deleter>;
    using Renderer = std::unique_ptr<SDL::Renderer, Deleter>;
    using Texture = std::unique_ptr<SDL::Texture, Deleter>;
    using Surface = std::unique_ptr<SDL::Surface, Deleter>;
}
