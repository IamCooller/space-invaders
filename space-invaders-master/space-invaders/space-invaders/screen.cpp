#include "screen.h"
#include <cstdio>

void Screen::show()
{
    m_renderSystem.initialize();
    m_renderSystem.forceClear();
    clock_t clockLastFrame = clock();
    while (m_isInfinite || m_showDuration > 0)
    {
        clock_t clockNow = clock();
        clock_t deltaClock = clockNow - clockLastFrame;
        float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
        clockLastFrame = clockNow;

        m_renderSystem.clear();
        render();
        m_renderSystem.flush();
        update(deltaTime);
        if (m_showDuration > 0)
        {
            m_showDuration -= deltaTime;
        }
    }
    m_renderSystem.forceClear();
}

void Screen::close()
{
    m_isInfinite = false;
    m_showDuration = 0;
}

void Screen::render()
{
    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "SCREEN PLACEHOLDER(%.2fs)", m_showDuration);
    int x = SCREEN_WIDTH / 2 - length / 2;
    getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_White, ConsoleColor_Black);
}

void Screen::update(float dt)
{

}
