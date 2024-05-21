#include "Plant.h"

Plant::Plant(int y, int x) : Organism(y, x) {
    _attempts_to_spread = 1;
    _is_animal = false;
    _spread_probability = 3;
}

void Plant::makeAction(std::vector<std::vector<organismType>>& grid,
    std::vector<std::unique_ptr<Organism>>& organisms) {
    Point curr_point = {_y, _x};

    _makeExtraAction(grid, organisms); // this is for Sosnowsky's hogweed

    for (int i = 0; i < _attempts_to_spread; ++i) {
        Point new_point = _getFreeRandomAdjacentPoint(grid, curr_point);
        if (new_point.y != -1 && new_point.x != -1) {
            if (_isSpread(_spread_probability)) { // 75% chance of spreading is the default
                organisms.push_back(clone(new_point.y, new_point.x));
                grid[new_point.y][new_point.x] = _type;

                std::string message = " spread to (" + std::to_string(new_point.y) + ", ";
                message += std::to_string(new_point.x) + ")";
                Display::printMessage(_type, message);
            }
        }
    }
}

bool Plant::_isSpread(int percent) const {
    int n = rand() % 100 + 1;
    if (n <= percent)
        return true;
    return false;
}


void Plant::_makeExtraAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) {}
