#pragma once
#include <vector>
#include <array>
#include <list>
#include "Input.h"
#include "Organism.h"
#include "Animal.h"
#include "Human.h"

const int GRID_WIDTH = 48; // possible range: 2-48
const int GRID_HEIGHT = 18; // range: 2-18

class World {
public:
    World();
    void makeTurn();
    void drawWorld();
    bool isEnd();
    void startGame();
private:
    int width, height;
    bool is_end;
    int turn;
    Human* human;
    std::unique_ptr<Human> human_tmp;
    std::vector<std::unique_ptr<Organism>> organisms;
    std::vector<std::vector<organismType>> grid;
    Display out;
    Input in;

    // keeps track of free cells at the start of the game
    std::list<Point> unoccupied_points;
    // randomly chooses a free point on the grid and "marks" it as occupied
    Point _getRandomPoint();
    bool _humanExists();
    // for adding organisms at the start of the game at random locations
    void _addOrganism(organismType type);
    // add each organism once (besides human)
    void _addEachOrganism();
    // for creating organisms at (y, x)
    std::unique_ptr<Organism> _createOrganism(organismType type, int y, int x);
    // save and load the game state
    bool _serialize(std::string filename) const;
    bool _deserialize(std::string filename);
};

// helper function for sorting
bool compareOrganisms(const std::unique_ptr<Organism>& a, const std::unique_ptr<Organism>& b);
