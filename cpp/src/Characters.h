#pragma once
#include <unordered_map>

// unicode characters might not work on every terminal and they are 2x times wider
// comment the next line, if you want to use ASCII chars
#define UNICODE_CHARS

enum organismType {DEFAULT, HUMAN, WOLF, SHEEP, FOX, TURTLE, ANTELOPE,
    GRASS, SOW_THISTLE, GUARANA, BELLADONNA, SOS_HOGWEED};

class Characters {
public:
    static void initChars();
#ifdef UNICODE_CHARS
    static std::unordered_map<int, wchar_t> chars;
#else
    static std::unordered_map<int, char> chars;
#endif
};


#ifdef UNICODE_CHARS

const wchar_t HUMAN_CHAR = 0x1F9CD;
const wchar_t WOLF_CHAR = 0x1F43A;
const wchar_t SHEEP_CHAR = 0x1F411;
const wchar_t FOX_CHAR = 0x1F98A;
const wchar_t TURTLE_CHAR = 0x1F422;
const wchar_t ANTELOPE_CHAR = 0x1F98C;
const wchar_t GRASS_CHAR = 0x1F331;
const wchar_t SOW_THISTLE_CHAR = 0x1F33C;
const wchar_t GUARANA_CHAR = 0x1F490;
const wchar_t BELLADONNA_CHAR = 0x1F342;
const wchar_t SOS_HOGWEED_CHAR = 0x1F4AE;

#else

const char HUMAN_CHAR = '@';
const char WOLF_CHAR = 'w';
const char SHEEP_CHAR = 's';
const char FOX_CHAR = 'f';
const char TURTLE_CHAR = 't';
const char ANTELOPE_CHAR = 'a';
const char GRASS_CHAR = 'g';
const char SOW_THISTLE_CHAR = 'o';
const char GUARANA_CHAR = 'u';
const char BELLADONNA_CHAR = 'b';
const char SOS_HOGWEED_CHAR = 'h';

#endif

const char DEFAULT_CHAR = '?';
