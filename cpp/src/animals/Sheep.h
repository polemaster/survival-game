#pragma once
#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(int y, int x);

    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
};
