#pragma once
#include "map-utilities.h"
#include <optional>

class Player {

    public:

        Player(const Coordinates<int>& mapCoordinates);
        void startMove(Direction direction);
        void stopMove();
        void keepMoving();
        bool isMoving();
        const Coordinates<float>& getCoordinates() const;

    private:
        
        Coordinates<float> coordinates{};

        std::optional<Move> movement{ std::nullopt };
};