#pragma once
#include "Animal.h"
#include "Input.h"

class Human : public Animal {
public:
    Human(int y, int x);
    void getAction(action act, int turn);
    Point _getNewPoint(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) const override;
    void draw(Display& out) const override;
    std::unique_ptr<Organism> clone(int y, int x) const override;
    void purify(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms, int turn);
    void _useSpecialAbility(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) override;
private:
    action _curr_action;
    bool _ability_on;
    int _last_ability; // stores the turn when the activity was last activated

    friend std::ostream& operator<<(std::ostream& os, const Human& h);
    friend std::istream& operator>>(std::istream& in, Human& h);
};
