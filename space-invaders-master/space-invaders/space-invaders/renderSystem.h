#pragma once

#include <Windows.h>
#include "consoleColor.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

struct ConsoleSymbolData
{
    char symbol;
    ConsoleColor symbolColor;
    ConsoleColor backgroundColor;

    bool operator==(ConsoleSymbolData other)
    {
        return symbol == other.symbol && symbolColor == other.symbolColor && backgroundColor == other.backgroundColor;
    }

    bool operator!=(ConsoleSymbolData other)
    {
        return !(*this == other);
    }
};

class RenderSystem
{
public:
    RenderSystem();

    void initialize();
    void clear();
    void forceClear();
    void drawChar(int x, int y, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor);
    void drawText(int x, int y, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor);
    void flush();

private:
    void setConsoleCursor(int x, int y);
    void setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor);

private:
    HANDLE m_consoleHandle;
    ConsoleSymbolData m_backBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
    ConsoleSymbolData m_screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
};