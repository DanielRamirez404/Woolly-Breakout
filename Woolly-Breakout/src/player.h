#pragma once
#include "map-utilities.h"
#include <optional>

class Player {

    public:

        Player(const Coordinates<int>& mapCoordinates);
        void move(Direction direction);
        const Coordinates<float>& getCoordinates() const;


    private:
        
        Coordinates<float> coordinates{};

};