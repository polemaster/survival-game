#include "Wolf.h"
#include "Display.h"

Wolf::Wolf(int y, int x) : Animal(y, x) {
    _strength = 9;
    _initiative = 5;
    _type = WOLF;
}

void Wolf::draw(Display& out) const {
    out.printch(WOLF_CHAR, _y, _x);
}

std::unique_ptr<Organism> Wolf::clone(int y, int x) const {
    return std::make_unique<Wolf>(y, x);
}
