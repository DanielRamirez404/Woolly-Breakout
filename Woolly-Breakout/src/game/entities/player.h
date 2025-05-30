#pragma once
#include "../map/utilities.h"
#include "move.h"
#include <optional>

class Player {

    public:

        Player(const Coordinates<int>& mapCoordinates);
        
        void setCoordinates(const Coordinates<float>& newCoordinates);

        void queueMove(Direction direction);
        std::optional<Coordinates<int>> getTargetedCoordinates();

        void startMove();
        void stopMove();
        void keepMoving();
        bool isMoving();

        const Coordinates<float>& getCoordinates() const;
        Coordinates<float>& getCoordinates();
        const Coordinates<int> getRoundedCoordinates() const;

    private:
        
        Coordinates<float> coordinates{};

        std::optional<Direction> queuedDirection{};
        std::optional<Move> movement{ std::nullopt };
};