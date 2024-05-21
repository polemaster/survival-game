#include "Organism.h"

Organism::Organism(int y, int x) {
    _x = x;
    _y = y;
    _strength = 0;
    _initiative = 0;
    _type = DEFAULT;
    _age = 0; // starting turn
}

int Organism::getInitiative() const {
    return _initiative;
}

int Organism::getAge() const {
    return _age;
}

organismType Organism::getType() const {
    return _type;
}

void Organism::increaseAge() {
    ++_age;
}

int Organism::getStrength() const {
    return _strength;
}

int Organism::getX() const {
    return _x;
}

int Organism::getY() const {
    return _y;
}

bool Organism::isAnimal() const {
    return _is_animal;
}

void Organism::setX(int x) {
    _x = x;
}

void Organism::setY(int y) {
    _y = y;
}

void Organism::setStrength(int strength) {
    _strength = strength;
}

void Organism::setAge(int age) {
    _age = age;
}

int Organism::_getOrganismIndexFromPosition(std::vector<std::unique_ptr<Organism>>& organisms, int y, int x) const {
    for (int i = 0; i < organisms.size(); ++i) {
        if (organisms[i] && organisms[i]->getX() == x && organisms[i]->getY() == y)
            return i;
    }
    return -1;
}

Point Organism::_getFreeRandomAdjacentPoint(const std::vector<std::vector<organismType>>& grid, Point p) const {
    Point result;

    std::vector<Point> v;
    if (p.x > 0 && grid[p.y][p.x - 1] == DEFAULT)
        v.emplace_back(p.y, p.x - 1);
    if (p.y > 0 && grid[p.y - 1][p.x] == DEFAULT)
        v.emplace_back(p.y - 1, p.x);
    if (p.y < grid.size() - 1 && grid[p.y + 1][p.x] == DEFAULT)
        v.emplace_back(p.y + 1, p.x);
    if (p.x < grid[0].size() - 1 && grid[p.y][p.x + 1] == DEFAULT)
        v.emplace_back(p.y, p.x + 1);

    if (v.size() == 0)
        return {-1, -1};

    int n = rand() % v.size();

    result = v[n];

    return result;
}

std::vector<Point> Organism::_getOccupiedAdjacentPoints(const std::vector<std::vector<organismType>>& grid) const {
    std::vector<Point> v;
    int height = grid.size();
    int width = grid[0].size();

    if (_y < height - 1 && grid[_y + 1][_x] != DEFAULT)
        v.emplace_back(_y + 1, _x);
    if (_y > 0 && grid[_y - 1][_x] != DEFAULT)
        v.emplace_back(_y - 1, _x);
    if (_x > 0 && grid[_y][_x - 1] != DEFAULT)
        v.emplace_back(_y, _x - 1);
    if (_x < width - 1 && grid[_y][_x + 1] != DEFAULT)
        v.emplace_back(_y, _x + 1);

    return v;
}

