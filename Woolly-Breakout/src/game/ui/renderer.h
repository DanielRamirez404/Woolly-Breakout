#pragma once
#include "elements.h"
#include <string>
#include <memory>
#include <unordered_map>

class Renderer {
    public:
        
        void setRenderer(SDL::Window* window);
        void setTransparentMode();

        void loadTexture(const std::string& name);

        void setArea(int x, int y, int width, int height);
        void setArea(int x, int y, int size);
        void setArea(int origin, int size);

        void addColor(int r, int g, int b, int a);
        void addTexture(const std::string& name);
        
        void clear();
        void render();

        operator bool() const;

    private:
        
        using textureMap = std::unordered_map<std::string, Smart::Texture>; 

        Smart::Renderer renderer{ nullptr };
        SDL::Rect area{};
        textureMap textures{};
};