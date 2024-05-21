#include "Guarana.h"

Guarana::Guarana(int y, int x) : Plant(y, x) {
    _type = GUARANA;
}

void Guarana::draw(Display &out) const {
    out.printch(GUARANA_CHAR, _y, _x);
}

std::unique_ptr<Organism> Guarana::clone(int y, int x) const {
    return std::make_unique<Guarana>(y, x);
}
