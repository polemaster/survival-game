#pragma once

#include "Plant.h"

class SowThistle : public Plant {
public:
    SowThistle(int y, int x);
    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
};
