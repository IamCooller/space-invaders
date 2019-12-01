#pragma once

#include "renderSystem.h"
#include <array>

using namespace std;

const int LEVEL_ROWS = SCREEN_HEIGHT;
const int LEVEL_COLS = SCREEN_WIDTH;

typedef const array<array<unsigned char, LEVEL_COLS + 1>, LEVEL_ROWS> LevelData;

class Level
{
public:
    LevelData getLevelData(int level);
    unsigned char getRenderCellSymbol(unsigned char cellSymbol);
    ConsoleColor getRenderCellSymbolColor(unsigned char cellSymbol);
    ConsoleColor getRenderCellSymbolBackgroundColor(unsigned char cellSymbol);
};

LevelData levelDataEmpty;
