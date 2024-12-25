#include "safe-zone.h"
#include "../map/utilities.h"
#include "../../constants/constants.h"
#include <algorithm>
#include <utility>

SafeZone::SafeZone(const Coordinates<int>& coordinates, const std::vector<Coordinates<int>>& keyList) 
    : doorCoordinates{coordinates} {
        for (int i{0}; i < Constants::SafeZone::totalKeys; ++i)
            keys.push_back(std::move(keyList[i]));
    }

void SafeZone::pickKeyUp(const Coordinates<int>& coordinates) {
    keys.remove(coordinates);
}

int SafeZone::getPickedUpKeys() const {
    return Constants::SafeZone::totalKeys - keys.size();
}

bool SafeZone::isKey(const Coordinates<int>& coordinates) {
    for (const auto& key : keys)
        if (key == coordinates)
            return true;

    return false;
}

bool SafeZone::isOpen() const {
    return !keys.empty();
}

const Coordinates<int>& SafeZone::getDoor() const {
    return doorCoordinates;
}

const std::list<Coordinates<int>> SafeZone::getKeys() const {
    return keys;
}