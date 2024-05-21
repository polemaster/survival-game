#include <iostream>
#include <cstdlib>
#include <ctime>
#include "World.h"

int main() {
    srand(time(NULL));
    Characters::initChars();
    World world;

    world.startGame();

    while ( !world.isEnd() ) {
        world.drawWorld();
        world.makeTurn();
    }


    return 0;
}
