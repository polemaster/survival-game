#include "Human.h"

Human::Human(int y, int x) : Animal(y, x) {
    _curr_action = NOTHING;
    _strength = 5;
    _initiative = 4;
    _type = HUMAN;
    _last_ability = -10;
}

void Human::getAction(action act, int turn) {
    _curr_action = act;
    if (_ability_on && turn > _last_ability + 5)
        _ability_on = false;
}


Point Human::_getNewPoint(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) const {


    Point result;
    // add adjacent points
    int height = grid.size();
    int width = grid[0].size();

    result = {_y, _x};
    switch(_curr_action) {
        case MOVE_DOWN:
            if (_y < height - 1)
                result = {_y + 1, _x};
            break;
        case MOVE_UP:
            if (_y > 0)
                result = {_y - 1, _x};
            break;
        case MOVE_LEFT:
            if (_x > 0)
                result = {_y, _x - 1};
            break;
        case MOVE_RIGHT:
            if (_x < width - 1)
                result = {_y, _x + 1};
            break;
    }

    return result;
}

void Human::draw(Display& out) const {
    out.printch(HUMAN_CHAR, _y, _x);
}

std::unique_ptr<Organism> Human::clone(int y, int x) const {
    return std::make_unique<Human>(y, x);
}

void Human::purify(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms, int turn) {

    if (_last_ability + 10 <= turn) {
        Display::printMessage(_type, " used ability Purify!");
        _ability_on = true;
        _last_ability = turn;
    }
}

void Human::_useSpecialAbility(std::vector<std::vector<organismType>>& grid,
std::vector<std::unique_ptr<Organism>>& organisms) {
    if (_ability_on) {
        std::vector<Point> v = _getOccupiedAdjacentPoints(grid);
        for (int i = 0; i < v.size(); ++i) {
            Point p = v[i];
            int index = _getOrganismIndexFromPosition(organisms, p.y, p.x);
            Display::printMessage(_type, " purified at (" + std::to_string(p.y) + ", " + std::to_string(p.x) + ") " , grid[p.y][p.x]);
            organisms[index].reset(nullptr);
            grid[p.y][p.x] = DEFAULT;
        }
    }
}
