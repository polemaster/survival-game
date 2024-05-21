#include "Display.h"
#include <locale.h>

const int INFO_BOX_HEIGHT = 9; // excluding border
const int INFO_BOX_COL_WIDTH = 29; // columns in info box (without border)

WINDOW* Display::info_win = nullptr;
int Display::curr_info_pos = 0;
int Display::max_info_pos = 0;


void Display::printMessage(const std::string& message) {
    if (curr_info_pos > max_info_pos)
        return;
    int start_x = (curr_info_pos / INFO_BOX_HEIGHT) * INFO_BOX_COL_WIDTH + 1;
    mvwaddstr(info_win, curr_info_pos % INFO_BOX_HEIGHT + 1, start_x, message.c_str());
    ++curr_info_pos;
    wrefresh(info_win);
}

void Display::printMessage(int type_one, const std::string& message, int type_two) {
    if (curr_info_pos > max_info_pos)
        return;
    int start_x = (curr_info_pos / INFO_BOX_HEIGHT) * INFO_BOX_COL_WIDTH + 1;
    wmove(info_win, curr_info_pos % INFO_BOX_HEIGHT + 1, start_x);
    _printChar(info_win, Characters::chars[type_one]);
    wprintw(info_win, message.c_str());
    _printChar(info_win, Characters::chars[type_two]);
    ++curr_info_pos;
    wrefresh(info_win);
}

void Display::printMessage(int type, const std::string& message) {
    if (curr_info_pos > max_info_pos)
        return;
    int start_x = (curr_info_pos / INFO_BOX_HEIGHT) * INFO_BOX_COL_WIDTH + 1;
    wmove(info_win, curr_info_pos % INFO_BOX_HEIGHT + 1, start_x);
    _printChar(info_win, Characters::chars[type]);
    wprintw(info_win, message.c_str());
    ++curr_info_pos;
    wrefresh(info_win);
}

void Display::_printChar(WINDOW* win, const wchar_t ch) {
    cchar_t final_char;
    setcchar(&final_char, &ch, 0, 0, NULL);
    wadd_wch(win, &final_char);
}

void Display::_printChar(WINDOW* win, const char ch) {
    waddch(win, ch);
}


void Display::clearInfoBox() {
    wclear(info_win);
    curr_info_pos = 0;
    box(info_win, 0, 0);
    wrefresh(info_win);
}

Display::Display(int height, int width) {
    setlocale(LC_ALL, ""); // enables UTF-8
    initscr();
    cbreak();
    noecho();
    start_color();
    curs_set(0); // sets cursor to be invisible


    getmaxyx(stdscr, max_y, max_x);

    windows.push_back(std::make_unique<LegendWindow>());

    _createNewGameWin(height, width);


    int info_box_width = max_x;
    // create info box window
    info_win = newwin(INFO_BOX_HEIGHT + 2, info_box_width, 0, 0);
    box(info_win, 0, 0);

    // set max info box position for displaying messages in info box
    int num_of_cols = (info_box_width / INFO_BOX_COL_WIDTH);
    max_info_pos = num_of_cols * INFO_BOX_HEIGHT - 1;

    refresh();
    wrefresh(info_win);
}

Display::~Display() {
    delwin(game_win);
    delwin(info_win);

    endwin();
}

WINDOW* Display::getGameWindow() {
    return game_win;
}

void Display::refreshGameWindow() {
    wrefresh(game_win);
}

void Display::clearGameWindow() {
    wclear(game_win);
    box(game_win, 0, 0);
    wrefresh(game_win);
}

void Display::_createNewGameWin(int height, int width) {
    // the unicode characters are 2x times wider
#ifdef UNICODE_CHARS
    width *= 2;
#endif

    // we add 2 for borders
    height += 2;
    width += 2;
    // we take the ending coordinates of the info box and legend, so we know where the game window starts
    int beg_x = windows[0]->getEndX();
    int beg_y = INFO_BOX_HEIGHT + 2;
    // here we center the game window
    beg_x = (max_x + beg_x) / 2 - width / 2;
    beg_y = (max_y + beg_y) / 2 - height / 2;
    // and finally we create it
    game_win = newwin(height, width, beg_y, beg_x);
    box(game_win, 0, 0);

    refresh();
    wrefresh(game_win);
}

void Display::resizeGameWindow(int height, int width) {
    delwin(game_win);

    _createNewGameWin(height, width);
}

void Display::printch(const wchar_t ch, int y, int x) {
    cchar_t final_char;
    setcchar(&final_char, &ch, 0, 0, NULL);
    x *= 2;
    mvwadd_wch(game_win, y + 1, x + 1, &final_char);
}

void Display::printch(char ch, int y, int x) {
    mvwaddch(game_win, y + 1, x + 1, ch);
}

void Display::refreshAllWindows() {
    clear();
    for (auto& win: windows)
        win->updateWindow();
    clearGameWindow();
    wclear(info_win);
    box(info_win, 0, 0);
    wrefresh(info_win);
}
