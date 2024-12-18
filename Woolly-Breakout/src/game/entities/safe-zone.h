#pragma once
#include "../map/utilities.h"
#include <list>

class SafeZone {
    public:

        void addKey(const Coordinates<int>& coordinates);
        void pickKeyUp(const Coordinates<int>& coordinates);
        void setDoor(const Coordinates<int>& coordinates);
        bool isKey(const Coordinates<int>& coordinates);
        bool isOpen() const;
        int getPickedUpKeys() const;
        const Coordinates<int>& getDoor() const;
        const std::list<Coordinates<int>> getKeys() const; 

    private:
        Coordinates<int> doorCoordinates{};
        std::list<Coordinates<int>> keys{};
};


