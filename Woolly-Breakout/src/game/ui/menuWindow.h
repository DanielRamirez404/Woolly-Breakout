#pragma once
#include "window.h"
#include <string>
#include <vector>
#include <functional>

class MenuWindow : public Window {
	public:
        
        struct Button {
            int x{};
            int y{};
            int width{};
            int length{};
            std::function<void()> onClick{};
            bool includes(int x_coor, int y_coor) { return (x_coor <= x + width && x_coor >= x) && (y_coor <= y + length && y_coor >= y); };
        };

        MenuWindow();
        
        void addButton(const std::string& texture, Button button);
        void addTexture(const std::string& texture, int x, int y, int width, int length);
        
        void run();

    private:

        std::vector<Button> buttons{};
        Button* getClickedButton(int x, int y);
};
