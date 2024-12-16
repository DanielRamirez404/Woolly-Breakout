#pragma once

namespace Constants {
    inline constexpr int windowSize{ 500 };
    inline constexpr int mapSize{ 5 };
    inline constexpr int tileSize{ windowSize / mapSize };
    inline constexpr int fps{ 24 };
    inline constexpr int moveFrames{ fps / 4 };
}
