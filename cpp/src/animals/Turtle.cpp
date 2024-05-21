#include "Turtle.h"

Turtle::Turtle(int y, int x) : Animal(y, x) {
    _strength = 2;
    _initiative = 1;
    _type = TURTLE;
}

void Turtle::draw(Display& out) const {
    out.printch(TURTLE_CHAR, _y, _x);
}

std::unique_ptr<Organism> Turtle::clone(int y, int x) const {
    return std::make_unique<Turtle>(y, x);
}

Point Turtle::_getNewPoint(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) const {
    int n = rand() % 100 + 1;
    if (n <= 75)
        return {-1, -1};
    return _getRandomAdjacentPoint(grid);
}
