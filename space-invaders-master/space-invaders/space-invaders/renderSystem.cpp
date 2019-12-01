#include "renderSystem.h"
#include <cstdio>

RenderSystem::RenderSystem()
{
    m_consoleHandle = 0;
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            m_backBuffer[y][x].symbol = 0;
            m_backBuffer[y][x].symbolColor = ConsoleColor_Grey;
            m_backBuffer[y][x].backgroundColor = ConsoleColor_Black;

            m_screenBuffer[y][x] = m_backBuffer[y][x];
        }
    }
}

void RenderSystem::initialize()
{
    m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(m_consoleHandle, &cursorInfo);
}

void RenderSystem::clear()
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            m_backBuffer[y][x].symbol = 0;
            m_backBuffer[y][x].symbolColor = ConsoleColor_Grey;
            m_backBuffer[y][x].backgroundColor = ConsoleColor_Black;
        }
    }
}

void RenderSystem::forceClear()
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            m_backBuffer[y][x].symbol = 0;
            m_backBuffer[y][x].symbolColor = ConsoleColor_Grey;
            m_backBuffer[y][x].backgroundColor = ConsoleColor_Black;

            m_screenBuffer[y][x] = m_backBuffer[y][x];

            setConsoleCursor(x, y);
            setConsoleColor(m_screenBuffer[y][x].symbolColor, m_screenBuffer[y][x].backgroundColor);
            printf("%c", m_screenBuffer[y][x].symbol);
        }
    }
    setConsoleCursor(0, 0);

}

void RenderSystem::drawChar(int x, int y, char symbol, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
    {
        return;
    }

    m_backBuffer[y][x].symbol = symbol;
    m_backBuffer[y][x].symbolColor = symbolColor;
    m_backBuffer[y][x].backgroundColor = backgroundColor;
}

void RenderSystem::drawText(int x, int y, const char* text, ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    int cx = x;
    char symbol = *text;

    while (symbol != 0)
    {
        drawChar(cx, y, symbol, symbolColor, backgroundColor);

        text++;
        cx++;
        symbol = *text;
    }
}

void RenderSystem::flush()
{
    bool screenBufferModified = false;

    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            if (m_backBuffer[y][x] != m_screenBuffer[y][x])
            {
                m_screenBuffer[y][x] = m_backBuffer[y][x];

                setConsoleCursor(x, y);
                setConsoleColor(m_screenBuffer[y][x].symbolColor, m_screenBuffer[y][x].backgroundColor);
                printf("%c", m_screenBuffer[y][x].symbol);
                screenBufferModified = true;
            }
        }
    }
    if (screenBufferModified)
    {
        setConsoleCursor(0, 0);
    }
}

void RenderSystem::setConsoleCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(m_consoleHandle, coord);
}

void RenderSystem::setConsoleColor(ConsoleColor symbolColor, ConsoleColor backgroundColor)
{
    unsigned char consoleColor = symbolColor | (backgroundColor << 4);
    SetConsoleTextAttribute(m_consoleHandle, consoleColor);
}
