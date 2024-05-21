#include <fstream>
#include <iostream>
#include <sstream>
#include "World.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Fox.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Grass.h"
#include "SowThistle.h"
#include "Guarana.h"
#include "Belladonna.h"
#include "SosnowskyHogweed.h"
#include <algorithm> // for sort()
#include <unistd.h> // for sleep()

const int END_WAIT_TIME = 5; // in seconds
const char* GAME_STATES_PATH = "../states/";


World::World() : width(GRID_WIDTH), height(GRID_HEIGHT),
grid(GRID_HEIGHT, std::vector<organismType>(GRID_WIDTH)), out(height, width) {
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            grid[i][j] = DEFAULT;

    is_end = false;
    turn = 1;
}

void World::startGame() {
    in.getWindow(out.getGameWindow());

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            unoccupied_points.emplace_back(i, j);

    // create human
    Point p = _getRandomPoint();
    human_tmp = std::make_unique<Human>(p.y, p.x);
    human = human_tmp.get();
    grid[p.y][p.x] = HUMAN;
    organisms.push_back(std::move(human_tmp));

    _addEachOrganism();
    _addEachOrganism();
    _addEachOrganism();
    _addEachOrganism();
    _addEachOrganism();
    _addEachOrganism();
    // _addOrganism(ANTELOPE);
    // _addOrganism(TURTLE);
    // _addOrganism(TURTLE);
    // _addOrganism(TURTLE);
    // _addOrganism(SHEEP);
    // _addOrganism(GUARANA);

    std::sort(organisms.begin(), organisms.end(), compareOrganisms);
}

void World::makeTurn() {
    action key;
    key = in.readKey();
    if (key != NOTHING) {
        out.clearInfoBox();
        Display::printMessage("turn " + std::to_string(turn));
    }
    if (key == QUIT_GAME)
        is_end = true;
    else if (key == MOVE_DOWN || key == MOVE_UP || key == MOVE_LEFT || key == MOVE_RIGHT) {
        ++turn;
        human->getAction(key, turn);

        // save the size, because the vector will change while iterating over it
        int size = organisms.size();
        for (int i = 0; i < size; ++i) {
            if (organisms[i]) {
                organisms[i]->increaseAge();
                organisms[i]->makeAction(grid, organisms);
            }
        }
        // remove all nullptr from the vector
        organisms.erase(std::remove(organisms.begin(), organisms.end(), nullptr), organisms.end());

        // check if human still exists
        if (!_humanExists()) {
            is_end = true;
            drawWorld();
            Display::clearInfoBox();
            Display::printMessage("You died. The end.");
            Display::printMessage("Number of turns survived: " + std::to_string(turn - 2));
            // getch();
            sleep(END_WAIT_TIME);
        }
        // check if you won
        else if (_humanExists() && organisms.size() == 1) {
            is_end = true;
            drawWorld();
            Display::clearInfoBox();
            Display::printMessage("Congratulations! You won!");
            Display::printMessage("Number of turns survived: " + std::to_string(turn - 1));
            sleep(END_WAIT_TIME);
            // getch();
        }
        else if (_humanExists() && organisms.size() == 0)
            throw std::invalid_argument("Human somehow alive");


        // sorting
        if (organisms.size() > 0)
            std::sort(organisms.begin(), organisms.end(), compareOrganisms);
    }
    else if (key == USE_ABILITY) {
        human->purify(grid, organisms, turn);
    }
    else if (key == SAVE_FILE) {
        std::string filename = in.getFilename();
        if (_serialize(filename)) {
            out.refreshAllWindows();
            Display::printMessage("Save game state to: " + filename);
        }
        else
            Display::printMessage("Couldn't open the file: " + filename);
    }
    else if (key == LOAD_FILE) {
        std::string filename = in.getFilename();
        if (_deserialize(filename)) {
            out.refreshAllWindows();
            Display::printMessage("Loaded game state from: " + filename);
        }
        else
            Display::printMessage("Couldn't open the file: " + filename);
    }
}

void World::drawWorld() {
    out.clearGameWindow();
    for (std::size_t i = 0; i < organisms.size(); ++i)
        organisms[i]->draw(out);
    out.refreshGameWindow();
}

bool World::isEnd() {
    return is_end;
}

bool World::_humanExists() {
    for (int i = 0; i < organisms.size(); ++i) {
        if (organisms[i] && organisms[i]->getType() == HUMAN)
            return true;
    }
    return false;
}

void World::_addEachOrganism() {
    for (int i = 2; i < 1 + PLANTS + ANIMALS; ++i)
        _addOrganism(static_cast<organismType>(i));
}

void World::_addOrganism(organismType type) {
    Point p = _getRandomPoint();
    grid[p.y][p.x] = type;
    std::unique_ptr<Organism> org = _createOrganism(type, p.y, p.x);
    organisms.push_back(std::move(org));
}

Point World::_getRandomPoint() {
    int max = unoccupied_points.size();
    if (max == 0) {
        throw std::logic_error("no more free points on the map");
    }
    Point result;
    int n = rand() % max;

    auto it = std::next(unoccupied_points.begin(), n); // Get an iterator to the n-th element
    result = std::move(*it); // Save the n-th element to a variable
    unoccupied_points.erase(it); // Remove the n-th element from the list

    return result;
}

bool compareOrganisms(const std::unique_ptr<Organism>& a, const std::unique_ptr<Organism>& b) {
    // sort by initiative
    if (a->getInitiative() != b->getInitiative()) {
        return a->getInitiative() > b->getInitiative();
    }
    // sort by age if initiative is the same
    return a->getAge() > b->getAge();
}

bool World::_serialize(std::string filename) const {
    std::ofstream outfile;
    // file.open(filename, std::ios::binary);
    outfile.open(GAME_STATES_PATH + filename);
    if (outfile.is_open()) {
        // save basic properties of the world
        outfile << width << " " << height << " " << is_end << " " << turn << std::endl;

        // save the grid
        for (const auto& row : grid) {
            for (const auto& elem : row) {
                outfile << elem << " ";
            }
            outfile << std::endl;
        }

        // save all the organisms
        outfile << organisms.size() << std::endl;
        for (const auto& organism : organisms) {
            outfile << *organism << std::endl;
        }

        outfile.close();
        return true;
    }
    else {
        return false;
    }
}

bool World::_deserialize(std::string filename) {
    std::ifstream infile(GAME_STATES_PATH + filename);

    if (infile.is_open()) {
        // clear the previous game state
        organisms.clear();
        grid.clear();

        // load basic variables
        infile >> width >> height >> is_end >> turn;

        grid.resize(height, std::vector<organismType>(width));

        // load the grid
        int org_type;
        organismType type;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                infile >> org_type;
                type = static_cast<organismType>(org_type);
                grid[i][j] = type;
            }
        }

        // load the organisms
        int num_of_organisms, y, x;
        infile >> num_of_organisms;
        for (int i = 0; i < num_of_organisms; ++i) {
            infile >> org_type >> y >> x;
            type = static_cast<organismType>(org_type);
            std::unique_ptr<Organism> new_org = _createOrganism(type, y, x);
            infile >> *new_org;
            if (type == HUMAN) {
                // human = static_cast<Human*>(new_org.get());
                human = dynamic_cast<Human*>(new_org.get());
                if (human == nullptr)
                    throw std::invalid_argument("Human incorrectly casted");
            }
            organisms.push_back(std::move(new_org));
        }

        // change out width and height
        out.resizeGameWindow(height, width);
        in.getWindow(out.getGameWindow());

        infile.close();
        return true;
    }
    else {
        return false;
    }
}


std::ostream& operator<<(std::ostream& os, const Organism& org) {
    os << org.getType() << " " << org.getY() << " " << org.getX();
    os << " " << org.getAge() << " " << org.getStrength();

    if (org.getType() == HUMAN) {
        const Human& human = static_cast<const Human&>(org);
        os << " " << human;
    }
    else if (!org.isAnimal()) {
        const Plant& plant = static_cast<const Plant&>(org);
        os << " " << plant;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const Human& h) {
    os << h._ability_on << " " << h._last_ability;

    return os;
}

std::ostream& operator<<(std::ostream& os, const Plant& p) {
    os << p._attempts_to_spread;

    return os;
}

std::istream& operator>>(std::istream& in, Organism& org) {
    int age, strength;

    in >> age >> strength;
    org.setStrength(strength);
    org.setAge(age);
    if (org.getType() == HUMAN) {
        Human& human = static_cast<Human&>(org);
        in >> human;
    }
    else if (!org.isAnimal()) {
        Plant& plant = static_cast<Plant&>(org);
        in >> plant;
    }
    return in;
}

std::istream& operator>>(std::istream& in, Human& h) {
    in >> h._ability_on >> h._last_ability;

    return in;
}

std::istream& operator>>(std::istream& in, Plant& p) {
    in >> p._attempts_to_spread;

    return in;
}

std::unique_ptr<Organism> World::_createOrganism(organismType type, int y, int x) {
    switch(type) {
        case HUMAN:
            return std::make_unique<Human>(y, x);
        case WOLF:
            return std::make_unique<Wolf>(y, x);
        case SHEEP:
            return std::make_unique<Sheep>(y, x);
        case FOX:
            return std::make_unique<Fox>(y, x);
        case TURTLE:
            return std::make_unique<Turtle>(y, x);
        case ANTELOPE:
            return std::make_unique<Antelope>(y, x);
        case GRASS:
            return std::make_unique<Grass>(y, x);
        case SOW_THISTLE:
            return std::make_unique<SowThistle>(y, x);
        case GUARANA:
            return std::make_unique<Guarana>(y, x);
        case BELLADONNA:
            return std::make_unique<Belladonna>(y, x);
        case SOS_HOGWEED:
            return std::make_unique<SosnowskyHogweed>(y, x);
        case DEFAULT:
            throw std::invalid_argument("Given wrong type to create organism");
    }
}
