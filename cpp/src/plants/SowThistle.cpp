#include "SowThistle.h"

SowThistle::SowThistle(int y, int x) : Plant(y, x) {
    _type = SOW_THISTLE;
    _attempts_to_spread = 3;
}

void SowThistle::draw(Display &out) const {
    out.printch(SOW_THISTLE_CHAR, _y, _x);
}

std::unique_ptr<Organism> SowThistle::clone(int y, int x) const {
    return std::make_unique<SowThistle>(y, x);
}
