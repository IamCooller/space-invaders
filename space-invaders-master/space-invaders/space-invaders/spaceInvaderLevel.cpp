#include "level.h"
#include "spaceInvadersObjects.h"
#include <array>

unsigned char Level::getRenderCellSymbol(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Player:      return 202;
    case CellSymbol_Bullet:      return 179;
    case CellSymbol_Alien:       return 6;
    case CellSymbol_AlienSpread: return 5;
    case CellSymbol_AlienBrood:  return 2;
    case CellSymbol_AlienTank:   return 4;
    }
}

ConsoleColor Level::getRenderCellSymbolColor(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Player:      return ConsoleColor_White;
    case CellSymbol_Bullet:      return ConsoleColor_Red;
    case CellSymbol_Alien:       return ConsoleColor_DarkGreen;
    case CellSymbol_AlienSpread: return ConsoleColor_Green;
    case CellSymbol_AlienBrood:  return ConsoleColor_Magenta;
    case CellSymbol_AlienTank:   return ConsoleColor_Red;
    }
}

ConsoleColor Level::getRenderCellSymbolBackgroundColor(unsigned char cellSymbol)
{
    switch (cellSymbol)
    {
    case CellSymbol_Player: return ConsoleColor_DarkGrey;
    }
    return ConsoleColor_Black;
}

LevelData levelData0 = {
    "                                                                                ",
    "       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       ",
    "         X  XXXX XX XXXXXXX  XXXXXXXXXXXXXXXXXXXXXX  XXXXXXX XX XXXX  X         ",
    "       XXXXXXXXX    X  X  X  X  XXX  XXXXXX  XXX  X  X  X  X    XXXXXXXXX       ",
    "            XXXX    X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X    XXXX            ",
    "            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
    "            X  X                  XXXXXXXXXXXX                  X  X            ",
    "                                  XX  XXXX  XX                                  ",
    "                                  XX  X  X  XX                                  ",
    "                                  X          X                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                       P                                        ",
};

LevelData levelData1 = {
    "                                                                                ",
    "       XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       ",
    "         X  XXXX XX SXXXXXS  XXXXXXXXXXXXXXXXXXXXXX  SXXXXXS XX XXXX  X         ",
    "       XXXXXXXXX    X  X  X  X  XSX  XXXXXX  XSX  X  X  X  X    XXXXXXXXX       ",
    "            XXXX S  X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X  S XXXX            ",
    "            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
    "            X  X                  XXXXXXXXXXXX                  X  X            ",
    "                                  XX  XXXX  XX                                  ",
    "                                  XX  X  X  XX                                  ",
    "                                  X    SS    X                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                       P                                        ",
};

LevelData levelData2 = {
    "                                                                                ",
    "       XXBXXXXXXXXXXXBXBXBXXXXBXXBXXXXBXXBXXXXBXXBXXXXBXBXBXXXXXXXXXXXBXX       ",
    "         X  XXXX XX XXXXXXX  XXXXXXXXXXXXXXXXXXXXXX  XXXXXXX XX XXXX  X         ",
    "       XXXXXXXXX    X  X  X  X  XXX  XXXXXX  XXX  X  X  X  X    XXXXXXXXX       ",
    "            XXXX S  X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X  S XXXX            ",
    "            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
    "            X  X                  XXXXXXXXXXXX                  X  X            ",
    "                                  XX  XXXX  XX                                  ",
    "                                  XX  X  X  XX                                  ",
    "                                  X    SS    X                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                       P                                        ",
};

LevelData levelData3 = {
    "                                                                                ",
    "       XXBXXXXXXXXXXXBXBXBXXXXBXXBXXXXBXXBXXXXBXXBXXXXBXBXBXXXXXXXXXXXBXX       ",
    "        TTT XXXX XX XTXTXTX  TTTTTTTTTTTTTTTTTTTTTT  XTXTXTX XX XXXX TTT        ",
    "       XXXXXXXXX    X  X  X  X  XXX  XXXXXX  XXX  X  X  X  X    XXXXXXXXX       ",
    "            XXXX S  X  X  X  XXXXXXX  XXXX  XXXXXXX  X  X  X  S XXXX            ",
    "            XXXX             X   XXXXXXXXXXXXXX   X             XXXX            ",
    "            X  X                  XXXXXXXXXXXX                  X  X            ",
    "                                  XX  XXXX  XX                                  ",
    "                                  XX  X  X  XX                                  ",
    "                                  X    SS    X                                  ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                                       P                                        ",
};

LevelData Level::getLevelData(int level)
{
    switch (level)
    {
    case 0: return levelData0;
    case 1: return levelData1;
    case 2: return levelData2;
    case 3: return levelData3;
    }
    return levelDataEmpty;
}
