#include "Sheep.h"

Sheep::Sheep(int y, int x) : Animal(y, x) {
    _strength = 4;
    _initiative = 4;
    _type = SHEEP;
}

void Sheep::draw(Display& out) const {
    out.printch(SHEEP_CHAR, _y, _x);
}

std::unique_ptr<Organism> Sheep::clone(int y, int x) const {
    return std::make_unique<Sheep>(y, x);
}
