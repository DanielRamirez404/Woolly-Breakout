#pragma once
#include "../map/utilities.h"
#include "move.h"
#include <optional>

class Player {

    public:

        Player(const Coordinates<int>& mapCoordinates);
        void queueMove(Direction direction);
        void startMove();
        void stopMove();
        void keepMoving();
        bool isMoving();
        const Coordinates<float>& getCoordinates() const;

    private:
        
        Coordinates<float> coordinates{};

        std::optional<Direction> queuedDirection{};
        std::optional<Move> movement{ std::nullopt };
};