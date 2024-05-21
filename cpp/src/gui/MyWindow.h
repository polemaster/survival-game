#pragma once
#include <ncurses.h>
#include "Characters.h"
#include <string.h>

const int ANIMALS = 6;
const int PLANTS = 5;
const int LEGEND_ITEMS = ANIMALS + PLANTS;

class MyWindow {
public:
    MyWindow() {
        win = nullptr;
        getmaxyx(stdscr, max_y, max_x);
    }
    ~MyWindow() {
        delwin(win);
    }
    void createWindow() {
        win = newwin(height, width, beg_y, beg_x);
        if (with_box)
            box(win, 0, 0);
        refresh();
    }
    void updateWindow() {
        if (with_box)
            box(win, 0, 0);
        wrefresh(win);
    }
    int getEndX() const { return beg_x + width; }
protected:
    WINDOW* win;
    int beg_y, beg_x;
    int width, height;
    int max_x, max_y;
    bool with_box;
};

class LegendWindow : public MyWindow {
public:
    LegendWindow() {
        width = 25;
        height = LEGEND_ITEMS + 2;
        beg_y = max_y - height - 4;
        beg_x = 0;
        with_box = true;
        curr_item = 1; // we start from 1 because of border
        createWindow();
        addItem("Human: ", HUMAN_CHAR);
        addItem("Wolf: ", WOLF_CHAR);
        addItem("Sheep: ", SHEEP_CHAR);
        addItem("Fox: ", FOX_CHAR);
        addItem("Turtle: ", TURTLE_CHAR);
        addItem("Antelope: ", ANTELOPE_CHAR);
        addItem("Grass: ", GRASS_CHAR);
        addItem("Sow thistle: ", SOW_THISTLE_CHAR);
        addItem("Guarana: ", GUARANA_CHAR);
        addItem("Belladonna: ", BELLADONNA_CHAR);
        addItem("Sosnowsky's hogweed: ", SOS_HOGWEED_CHAR);
        updateWindow();
    }
private:
    int curr_item;
    void addItem(const char* txt, const char ch) {
        mvwaddstr(win, curr_item, 1, txt);
        waddch(win, ch);
        ++curr_item;
    }
    void addItem(const char* txt, const wchar_t ch) {
        mvwaddstr(win, curr_item, 1, txt);

        cchar_t final_char;
        setcchar(&final_char, &ch, 0, 0, NULL);
        wadd_wch(win, &final_char);

        ++curr_item;
    }
};
