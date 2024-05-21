#include "Belladonna.h"

Belladonna::Belladonna(int y, int x) : Plant(y, x) {
    _type = BELLADONNA;
    _strength = 99;
}

void Belladonna::draw(Display &out) const {
    out.printch(BELLADONNA_CHAR, _y, _x);
}

std::unique_ptr<Organism> Belladonna::clone(int y, int x) const {
    return std::make_unique<Belladonna>(y, x);
}
