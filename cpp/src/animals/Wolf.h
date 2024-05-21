#pragma once
#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(int y, int x);

    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
};
