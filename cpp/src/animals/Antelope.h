#pragma once
#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(int y, int x);

    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
    Point _getNewPoint(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) const override;
    bool _madeAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms, int org_index) override;
};
