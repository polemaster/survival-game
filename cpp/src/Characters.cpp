#include "Characters.h"

#ifdef UNICODE_CHARS
std::unordered_map<int, wchar_t> Characters::chars;
#else
std::unordered_map<int, char> Characters::chars;
#endif

void Characters::initChars() {
    chars[HUMAN] = HUMAN_CHAR;
    chars[WOLF] = WOLF_CHAR;
    chars[SHEEP] = SHEEP_CHAR;
    chars[FOX] = FOX_CHAR;
    chars[TURTLE] = TURTLE_CHAR;
    chars[ANTELOPE] = ANTELOPE_CHAR;
    chars[GRASS] = GRASS_CHAR;
    chars[SOW_THISTLE] = SOW_THISTLE_CHAR;
    chars[GUARANA] = GUARANA_CHAR;
    chars[BELLADONNA] = BELLADONNA_CHAR;
    chars[SOS_HOGWEED] = SOS_HOGWEED_CHAR;
}
