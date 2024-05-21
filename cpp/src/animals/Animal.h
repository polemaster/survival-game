#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
    Animal(int y, int x);
    void makeAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms);
    virtual void draw(Display& out) const = 0;
    virtual std::unique_ptr<Organism> clone(int y, int x) const = 0;
    Point getPoint() const { return _old_point; }
protected:
    virtual Point _getNewPoint(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) const;
    virtual void _handleCollision(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms);
    virtual void _useSpecialAbility(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms);
    virtual bool _madeAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms, int org_index);
    Point _getRandomAdjacentPoint(const std::vector<std::vector<organismType>>& grid) const;
    void _updateGrid(std::vector<std::vector<organismType>>& grid);
    void _updateCurrPoint();
    Point _old_point;
    Point _new_point;
private:
    Point _getOneOfAdjacentPoints(const std::vector<std::vector<organismType>>& grid) const;
    bool _isDead(int org_index, std::vector<std::unique_ptr<Organism>>& organisms);
};

