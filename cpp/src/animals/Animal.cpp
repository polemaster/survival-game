#include "Animal.h"

Animal::Animal(int y, int x) : Organism(y, x) {
    _new_point = {y, x};
    _old_point = {y, x};
    _is_animal = true;
}

void Animal::makeAction(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) {
    _old_point = {_y, _x};
    _new_point = _getNewPoint(grid, organisms);

    // doesn't allow special ability
    if ((_old_point.x == _new_point.x && _old_point.y == _new_point.y) || _new_point.x == -1)
        return;

    using namespace std;


    // if the new point is empty, move there
    if (grid[_new_point.y][_new_point.x] == DEFAULT) {
        // string txt = " moved from (" + to_string(_old_point.y) + ", " + to_string(_old_point.x) + ") to (";
        // txt += to_string(_new_point.y) + ", " + to_string(_new_point.x) + ")";
        string txt = " moved to (" + to_string(_new_point.y) + ", " + to_string(_new_point.x) + ")";
        Display::printMessage(_type, txt);

        _updateGrid(grid);
        _updateCurrPoint();
    }
    // if the organism on the new point is of the same type, reproduce
    else if (grid[_new_point.y][_new_point.x] == _type) {
        Point p = _getOneOfAdjacentPoints(grid);
        if (p.y != -1 && p.x != -1) {
            grid[p.y][p.x] = _type;
            organisms.push_back(clone(p.y, p.x));
            string txt = " was created at: (" + to_string(p.y) + ", " + to_string(p.x) + ")";
            Display::printMessage(_type, txt);
        }
    }
    // if different type, resolve conflict
    else {
        _handleCollision(grid, organisms);
    }
    if (grid[_y][_x] == HUMAN) // if human was not deleted
        _useSpecialAbility(grid, organisms);
}


void Animal::_handleCollision(std::vector<std::vector<organismType>>& grid,
        std::vector<std::unique_ptr<Organism>>& organisms) {

    int org_index = _getOrganismIndexFromPosition(organisms, _new_point.y, _new_point.x);
    if (org_index == -1)
        throw std::invalid_argument("Organism not found");

    // if one of the organisms is Antelope, they have 50% chance to avoid fight and the turtle
    // reflects enemies with strength less than 5
    if (_madeAction(grid, organisms, org_index))
        return;

    // if you have less strength or encounter a lethal plant, you die
    if (_isDead(org_index, organisms)) {
        if (organisms[org_index]->isAnimal())
            Display::printMessage(_type, " died trying to kill ", organisms[org_index]->getType());
        else
            Display::printMessage(_type, " died eating ", organisms[org_index]->getType());
        int current = _getOrganismIndexFromPosition(organisms, _old_point.y, _old_point.x);
        organisms[current].reset(nullptr);
        grid[_old_point.y][_old_point.x] = DEFAULT;
    }
    // if you have more or equal strength, you win
    else {
        if (organisms[org_index]->isAnimal())
            Display::printMessage(_type, " killed ", organisms[org_index]->getType());
        else if (organisms[org_index]->getType() == GUARANA) {
            _strength += 3;
            Display::printMessage(_type, " gained 3 strength eating ", organisms[org_index]->getType());
        }
        else
            Display::printMessage(_type, " ate ", organisms[org_index]->getType());

        organisms[org_index].reset(nullptr);
        _updateGrid(grid);
        _updateCurrPoint();
    }

}

void Animal::_useSpecialAbility(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) {
}

bool Animal::_madeAction(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms, int org_index) {
    if (organisms[org_index]->getType() == ANTELOPE) {
        if (_type != ANTELOPE && (rand() % 2 == 1)) {
            Point p = _getFreeRandomAdjacentPoint(grid, _new_point);
            if (p.x != -1) {
                std::string message = " ran away to: (" + std::to_string(p.y) + ", " + std::to_string(p.x) + ")";
                Display::printMessage(ANTELOPE, message);
                organisms[org_index]->setY(p.y);
                organisms[org_index]->setX(p.x);
                grid[p.y][p.x] = ANTELOPE;
                _updateGrid(grid);
                _updateCurrPoint();
                return true;
            }
        }
    }
    // if you attack turtle and have strength less than 5, end collision (return true)
    if (organisms[org_index]->getType() == TURTLE && _strength < 5) {
        Display::printMessage(organisms[org_index]->getType(), " deflected attack of ", _type);
        return true;
    }
    return false;
}

bool Animal::_isDead(int org_index, std::vector<std::unique_ptr<Organism>>& organisms) {
    if (_strength < organisms[org_index]->getStrength() ||
    organisms[org_index]->getType() == BELLADONNA || organisms[org_index]->getType() == SOS_HOGWEED)
        return true;

    return false;
}

Point Animal::_getNewPoint(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) const {
    return _getRandomAdjacentPoint(grid);
}

Point Animal::_getRandomAdjacentPoint(const std::vector<std::vector<organismType>>& grid) const {
    Point result;
    // add adjacent points
    std::vector<Point> v;
    if (_x > 0)
        v.emplace_back(_y, _x - 1);
    if (_y > 0)
        v.emplace_back(_y - 1, _x);
    if (_y < grid.size() - 1)
        v.emplace_back(_y + 1, _x);
    if (_x < grid[0].size() - 1)
        v.emplace_back(_y, _x + 1);

    // there should be always an adjacent square because we take into account the occupied ones as well
    if (v.size() == 0)
        throw std::logic_error("no empty adjacent cells");
    int n = rand() % v.size();

    result = v[n];

    return result;
}

Point Animal::_getOneOfAdjacentPoints(const std::vector<std::vector<organismType>>& grid) const {
    Point result;
    Point p1 = _getFreeRandomAdjacentPoint(grid, _old_point);
    Point p2 = _getFreeRandomAdjacentPoint(grid, _new_point);

    if (p1.x == -1 && p2.x != -1)
        return p2;
    else if (p1.x != -1 && p2.x == -1)
        return p1;

    std::vector<Point> v;
    v.push_back(p1);
    v.push_back(p2);

    int n = rand() % 2;
    result = v[n];

    return result;
}

void Animal::_updateCurrPoint() {
    _y = _new_point.y;
    _x = _new_point.x;
}

void Animal::_updateGrid(std::vector<std::vector<organismType>>& grid) {
    grid[_old_point.y][_old_point.x] = DEFAULT;
    grid[_new_point.y][_new_point.x] = _type;
}
