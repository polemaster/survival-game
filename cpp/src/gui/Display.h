#pragma once
#include "MyWindow.h"
#include <vector>
#include <memory>
#include <string>


class Display {
public:
    Display(int height, int width);
    ~Display();
    WINDOW* getGameWindow();
    void refreshGameWindow();
    void refreshAllWindows();
    void clearGameWindow();
    void resizeGameWindow(int height, int width);
    void printch(wchar_t ch, int y, int x);
    void printch(char ch, int y, int x);
    static void printMessage(const std::string& message);
    static void printMessage(int type_one, const std::string& message, int type_two);
    static void printMessage(int type, const std::string& message);
    static void clearInfoBox();
private:
    WINDOW* game_win;
    static WINDOW* info_win;
    static int curr_info_pos;
    static int max_info_pos;
    std::vector<std::unique_ptr<MyWindow>> windows;
    int max_x, max_y;

    // helper functions (for printing organism char in info box)
    static void _printChar(WINDOW* win, const wchar_t ch);
    static void _printChar(WINDOW* win, const char ch);

    void _createNewGameWin(int height, int width);
};
