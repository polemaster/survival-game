#pragma once
#include "Organism.h"

class Plant : public Organism {
public:
    Plant(int y, int x);
    void makeAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms);
    virtual void draw(Display& out) const = 0;
    virtual std::unique_ptr<Organism> clone(int y, int x) const = 0;
protected:
    virtual void _makeExtraAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms);
    int _attempts_to_spread;
    int _spread_probability; // chance that it will spread (in %)

    friend std::ostream& operator<<(std::ostream& os, const Plant& p);
    friend std::istream& operator>>(std::istream& in, Plant& p);
private:
    bool _isSpread(int percent) const;
};
