#pragma once

namespace Constants {
    
    namespace Window {
        inline constexpr int size{ 500 };
    }

    namespace StatusBar {
        inline constexpr int length{ Window::size / 6 };

        namespace Frame {
            inline constexpr int size{ Window::size / 8 };
            inline constexpr int padding{ StatusBar::length - size };
        }
    }

    namespace Map {
        inline constexpr int length{ Window::size - StatusBar::length };
        
        namespace Matrix {
            inline constexpr int size{ 5 };
        }

        namespace TileRendering {
            inline constexpr int perRow{ 5 }; // must be odd
            inline constexpr int center{ (perRow + 1) / 2 };
            inline constexpr int size{ Window::size / perRow };
            inline constexpr int players{ Window::size - center * size };
        }
    }

    namespace Frames {
        inline constexpr int fps{ 24 };
        inline constexpr int perMove{ fps / 4 };
    }
}