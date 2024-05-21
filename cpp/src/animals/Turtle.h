#pragma once
#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(int y, int x);

    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
    Point _getNewPoint(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) const override;
};
