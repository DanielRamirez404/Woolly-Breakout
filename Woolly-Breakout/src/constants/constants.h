#pragma once

namespace Constants {
    inline constexpr int windowSize{ 500 };
    inline constexpr int statusBarLength{ windowSize / 6 };
    inline constexpr int mapLength{ windowSize - statusBarLength };
    inline constexpr int mapSize{ 5 };
    inline constexpr int renderedTilesPerRow{ 5 }; //must be odd
    inline constexpr int middleRenderedTile{ (renderedTilesPerRow + 1) / 2 };
    inline constexpr int tileSize{ windowSize / renderedTilesPerRow };
    inline constexpr int playersTileStart{ windowSize - middleRenderedTile * tileSize };
    inline constexpr int fps{ 24 };
    inline constexpr int moveFrames{ fps / 4 };
    inline constexpr int frameSize{ windowSize / 8 };
    inline constexpr int framePadding{ (statusBarLength - frameSize) / 2 };
}
