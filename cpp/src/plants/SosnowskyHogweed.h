#pragma once

#include "Plant.h"

class SosnowskyHogweed : public Plant {
public:
    SosnowskyHogweed(int y, int x);
    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
    void _makeExtraAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) override;
};
