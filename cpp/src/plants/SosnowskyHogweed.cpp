#include "SosnowskyHogweed.h"

SosnowskyHogweed::SosnowskyHogweed(int y, int x) : Plant(y, x) {
    _type = SOS_HOGWEED;
    _strength = 10;
}

void SosnowskyHogweed::draw(Display &out) const {
    out.printch(SOS_HOGWEED_CHAR, _y, _x);
}

std::unique_ptr<Organism> SosnowskyHogweed::clone(int y, int x) const {
    return std::make_unique<SosnowskyHogweed>(y, x);
}

void SosnowskyHogweed::_makeExtraAction(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) {
    Point curr_point;
    std::vector<Point> v = _getOccupiedAdjacentPoints(grid);

    Point result;
    // int height = grid.size();
    // int width = grid[0].size();


    // if (_y < height - 1 && grid[_y + 1][_x] != DEFAULT)
    //     v.emplace_back(_y + 1, _x);
    // if (_y > 0 && grid[_y - 1][_x] != DEFAULT)
    //     v.emplace_back(_y - 1, _x);
    // if (_x > 0 && grid[_y][_x - 1] != DEFAULT)
    //     v.emplace_back(_y, _x - 1);
    // if (_x < width - 1 && grid[_y][_x + 1] != DEFAULT)
    //     v.emplace_back(_y, _x + 1);

    for (int i = 0; i < v.size(); ++i) {
        curr_point = v[i];
        int index = _getOrganismIndexFromPosition(organisms, curr_point.y, curr_point.x);
        if (organisms[index]->isAnimal()) {
            grid[curr_point.y][curr_point.x] = DEFAULT;
            Display::printMessage(_type, " killed ", organisms[index]->getType());
            organisms[index].reset(nullptr);
        }
    }
}
