#include "safe-zone.h"
#include "map-utilities.h"
#include <algorithm>

void SafeZone::addKey(const Coordinates<int>& coordinates) {
    keys.push_back(coordinates);
}

void SafeZone::setDoor(const Coordinates<int>& coordinates) {
    doorCoordinates = coordinates;
}

void SafeZone::pickKeyUp(const Coordinates<int>& coordinates) {
    keys.remove(coordinates);
}

int SafeZone::getPickedUpKeys() const {
    return 3 - keys.size();
}

bool SafeZone::isKey(const Coordinates<int>& coordinates) {
    for (const auto& key : keys)
        if (key == coordinates)
            return true;

    return true;
}

#include <iostream>

bool SafeZone::isOpen() const {
    return keys.empty();
}

const Coordinates<int>& SafeZone::getDoor() const {
    return doorCoordinates;
}

const std::list<Coordinates<int>> SafeZone::getKeys() const {
    return keys;
}