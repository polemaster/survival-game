#include "Grass.h"

Grass::Grass(int y, int x) : Plant(y, x) {
    _type = GRASS;
}

void Grass::draw(Display &out) const {
    out.printch(GRASS_CHAR, _y, _x);
}

std::unique_ptr<Organism> Grass::clone(int y, int x) const {
    return std::make_unique<Grass>(y, x);
}
