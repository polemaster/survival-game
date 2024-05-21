#include "Input.h"
#include <memory>

Input::Input() : input_win(NULL) {}

void Input::getWindow(WINDOW* win) {
    input_win = win;
    keypad(input_win, true);
}

action Input::readKey() {
    int c = wgetch(input_win);
    switch(c) {
        case 'q':
            return QUIT_GAME;
        case KEY_UP:
            return MOVE_UP;
        case KEY_DOWN:
            return MOVE_DOWN;
        case KEY_LEFT:
            return MOVE_LEFT;
        case KEY_RIGHT:
            return MOVE_RIGHT;
        case 'a':
            return USE_ABILITY;
        case 's':
            return SAVE_FILE;
        case 'l':
            return LOAD_FILE;
    }
    return NOTHING;
}

std::string Input::getFilename() const {
    clear();
    echo();
    nocbreak();


    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);
    int height = 3;
    int width = max_x;
    int beg_y = 3;
    int beg_x = 0;
    WINDOW* file_win = newwin(height, width, beg_y, beg_x);
    box(file_win, 0, 0);
    refresh();
    wrefresh(file_win);

    wprintw(file_win, "Give filename:");

    int max_size = width - 2;
    auto str = std::make_unique<char[]>(max_size);
    mvwgetnstr(file_win, 1, 1, str.get(), max_size);

    std::string result = str.get();

    delwin(file_win);

    noecho();
    cbreak();
    return result;
}
