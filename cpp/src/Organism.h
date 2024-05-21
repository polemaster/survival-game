#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Display.h"

struct Point {
    int y;
    int x;

    Point(int y_coord, int x_coord) : y(y_coord), x(x_coord) {}
    Point() : y(0), x(0) {}
};


class Organism {
public:
    Organism(int y, int x);
    virtual void makeAction(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) = 0;
    virtual void draw(Display& out) const = 0;
    virtual std::unique_ptr<Organism> clone(int y, int x) const = 0;
    int getInitiative() const;
    int getAge() const;
    int getStrength() const;
    int getX() const;
    int getY() const;
    organismType getType() const;
    void setX(int x);
    void setY(int y);
    void setStrength(int strength);
    void setAge(int age);
    void increaseAge();
    bool isAnimal() const;
protected:
    int _initiative;
    int _strength;
    int _age;
    int _x, _y;
    organismType _type;
    bool _is_animal;

    int _getOrganismIndexFromPosition(std::vector<std::unique_ptr<Organism>>& organisms, int y, int x) const;
    Point _getFreeRandomAdjacentPoint(const std::vector<std::vector<organismType>>& grid, Point p) const;
    std::vector<Point> _getOccupiedAdjacentPoints(const std::vector<std::vector<organismType>>& grid) const;

    friend std::ostream& operator<<(std::ostream& os, const Organism& o);
    friend std::istream& operator>>(std::istream& in, Organism& o);
};
