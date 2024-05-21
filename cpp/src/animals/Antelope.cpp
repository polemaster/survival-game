#include "Antelope.h"

Antelope::Antelope(int y, int x) : Animal(y, x) {
    _strength = 4;
    _initiative = 4;
    _type = ANTELOPE;
}

void Antelope::draw(Display& out) const {
    out.printch(ANTELOPE_CHAR, _y, _x);
}

std::unique_ptr<Organism> Antelope::clone(int y, int x) const {
    return std::make_unique<Antelope>(y, x);
}

Point Antelope::_getNewPoint(std::vector<std::vector<organismType>>& grid,
    std::vector<std::unique_ptr<Organism>>& organisms) const {

    Point result;
    // add adjacent points
    std::vector<Point> v;
    if (_x > 1)
        v.emplace_back(_y, _x - 2);
    else if (_x > 0)
        v.emplace_back(_y, _x - 1);
    if (_y > 1)
        v.emplace_back(_y - 2, _x);
    else if (_y > 0)
        v.emplace_back(_y - 1, _x);
    if (_y < grid.size() - 2)
        v.emplace_back(_y + 2, _x);
    else if (_y < grid.size() - 1)
        v.emplace_back(_y + 1, _x);
    if (_x < grid[0].size() - 2)
        v.emplace_back(_y, _x + 2);
    else if (_x < grid[0].size() - 1)
        v.emplace_back(_y, _x + 1);

    if (v.size() == 0)
        throw std::logic_error("no empty adjacent cells");
    int n = rand() % v.size();

    result = v[n];

    return result;
}

bool Antelope::_madeAction(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms, int org_index) {
    if (rand() % 2 == 1) {
        Point p = Organism::_getFreeRandomAdjacentPoint(grid, _old_point);
        if (p.x != -1) {
            _new_point = p;
            Display::printMessage(_type, " ran away!");
            Animal::_updateGrid(grid);
            Animal::_updateCurrPoint();
            return true;
        }
    }
    return Animal::_madeAction(grid, organisms, org_index);
}
