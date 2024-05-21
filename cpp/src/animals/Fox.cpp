#include "Fox.h"

Fox::Fox(int y, int x) : Animal(y, x) {
    _strength = 3;
    _initiative = 7;
    _type = FOX;
}

void Fox::draw(Display& out) const {
    out.printch(FOX_CHAR, _y, _x);
}

std::unique_ptr<Organism> Fox::clone(int y, int x) const {
    return std::make_unique<Fox>(y, x);
}

Point Fox::_getNewPoint(std::vector<std::vector<organismType>>& grid,
    std::vector<std::unique_ptr<Organism>>& organisms) const {

    std::vector<Point> v;
    int height = grid.size();
    int width = grid[0].size();

    // add occupied spaces with weaker organisms
    if (_y < height - 1 && grid[_y + 1][_x] != DEFAULT) {
        int index = _getOrganismIndexFromPosition(organisms, _y + 1, _x);
        if (_strength >= organisms[index]->getStrength())
            v.emplace_back(_y + 1, _x);
    }
    if (_y > 0 && grid[_y - 1][_x] != DEFAULT) {
        int index = _getOrganismIndexFromPosition(organisms, _y - 1, _x);
        if (_strength >= organisms[index]->getStrength())
            v.emplace_back(_y - 1, _x);
    }
    if (_x > 0 && grid[_y][_x - 1] != DEFAULT) {
        int index = _getOrganismIndexFromPosition(organisms, _y, _x - 1);
        if (_strength >= organisms[index]->getStrength())
            v.emplace_back(_y, _x - 1);
    }
    if (_x < width - 1 && grid[_y][_x + 1] != DEFAULT) {
        int index = _getOrganismIndexFromPosition(organisms, _y, _x + 1);
        if (_strength >= organisms[index]->getStrength())
            v.emplace_back(_y, _x + 1);
    }

    // now add empty places
    if (_y < height - 1 && grid[_y + 1][_x] == DEFAULT)
        v.emplace_back(_y + 1, _x);
    if (_y > 0 && grid[_y - 1][_x] == DEFAULT)
        v.emplace_back(_y - 1, _x);
    if (_x > 0 && grid[_y][_x - 1] == DEFAULT)
        v.emplace_back(_y, _x - 1);
    if (_x < width - 1 && grid[_y][_x + 1] == DEFAULT)
        v.emplace_back(_y, _x + 1);

    // if there are no such points, don't do anything
    if (v.size() == 0)
        return {-1, -1};

    // finally get random point from the vector
    int n = rand() % v.size();


    return v[n];
}
