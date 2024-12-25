#pragma once
#include "../map/utilities.h"
#include "../../constants/constants.h"
#include <list>
#include <vector>

class SafeZone {
    public:

        SafeZone(const Coordinates<int>& coordinates, const std::vector<Coordinates<int>>& keyList);
        
        void pickKeyUp(const Coordinates<int>& coordinates);
        bool isKey(const Coordinates<int>& coordinates);
        bool isOpen() const;
        int getPickedUpKeys() const;
        const Coordinates<int>& getDoor() const;
        const std::list<Coordinates<int>> getKeys() const; 

    private:
        Coordinates<int> doorCoordinates{};
        std::list<Coordinates<int>> keys{};
};


