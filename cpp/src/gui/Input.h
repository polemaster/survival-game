#pragma once
#include <ncurses.h>
#include <string>

enum action {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, USE_ABILITY, QUIT_GAME, NOTHING,
SAVE_FILE, LOAD_FILE};

class Input {
public:
    Input();
    void getWindow(WINDOW* win);
    action readKey();
    std::string getFilename() const;
private:
    WINDOW* input_win;
};
