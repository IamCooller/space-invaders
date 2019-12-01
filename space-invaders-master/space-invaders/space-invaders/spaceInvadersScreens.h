#pragma once

#include "screen.h"
#include "consoleColor.h"
#include "input.h"

static ConsoleColor GetSymbolColor(unsigned char symbol)
{
    switch (symbol)
    {
    case 'Y': return ConsoleColor_Yellow;
    case 'G': return ConsoleColor_Green;
    case 'B': return ConsoleColor_Black;
    case 'R': return ConsoleColor_Red;
    }
    return ConsoleColor_Black;
}

const unsigned char logoData[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    "                                                                                ",
    "                                                                                ",
    "                                                                                ",
    "                      G        YYY     YYY     YYY     GG            GGGGGGG    ",
    "                     GGG     YYYYYYYYYYYYYYYYYYYYYYYYY  GGG         GGGGGGGGG   ",
    "                     GGGG   YYYYYYYYYYYYYYYYYYYYYYYYYYY  GGG         GGGG  GGG  ",
    "                      GGGG   YYYYYYYYYYYYYYYYYYYYYYYYYY   GGGG       GGGG   GGG ",
    "          GGGGG        GGGG   YYYYYYYYYYYYYYYYYYYYYYYY     GGGG      GGGG   GGG ",
    "   G    GGGGGGGG       GGGG    YYYYYYYYYYYYYYYYYYYYYY       GGGG    GGGG    GG  ",
    "   GG  GGGG  GGG      GGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGG     GGGGG  GGGGG    G   ",
    "   GGGGGG    GGGG   GGGGGG  GGGGGGGGGGGGGGGGGGGGGGGGGGGG    GGGGG GGGGG         ",
    "    GGGG    GGGG   GGGGGG  GGGGGRRRRRGGGGGGGGGGRRRRRGGGGG  GGGGGGGGGGG          ",
    "           GGGGGG GGGGGGGGGGGGGRRRRRRRGGGGGGGGRRRRRRRGGGGGGGGGGGGGGGG           ",
    "          GGGGGGGGGGGGGGGGGGGGGGRRRRRGGGGGGGGGGRRRRRGGGGGGGGGGGGGGGGGG          ",
    "         GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG         ",
    "        GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG        ",
    "       GGGGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGGGG       ",
    "       GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG       ",
    "       GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG       ",
    "        GGGGGGGGGGGGGGGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBGGGGGGGGGGGGGGGGGGG        ",
    "         GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG         ",
    "           GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG           ",
    "             GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG             ",
    "                                                                                ",
    "                                                                                "
};

class Logo : public Screen
{
public:
    Logo() : Screen(4) {}

protected:
    void render() {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                getRenderSystem()->drawChar(x, y, ' ', GetSymbolColor(logoData[y][x]), GetSymbolColor(logoData[y][x]));
            }
        }

        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "SPACE INVADERS");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, 1, buffer, ConsoleColor_Blue, ConsoleColor_Black);


        float loaded = getTotalTime() - getRemainedTime();
        float percent = loaded / getTotalTime();
        int fill = int(float(SCREEN_WIDTH) * percent);

        for (int i = 0; i <= fill; i++)
        {
            getRenderSystem()->drawChar(i, SCREEN_HEIGHT-1, ' ', ConsoleColor_DarkBlue, ConsoleColor_DarkBlue);
        }
    }
};

class Menu : public Screen
{
public:
    Menu() : Screen()
    {
        m_selected = 0;
        m_menuItems = 2;
    }

    int getSelected() { return m_selected; }

protected:
    void render()
    {
        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "SPACE INVADERS");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, 1, buffer, ConsoleColor_Blue, ConsoleColor_Black);
        
        int y = SCREEN_HEIGHT / 2 - m_menuItems;
        for (int i = 0; i < m_menuItems; i++)
        {
            ConsoleColor background = i == m_selected ? ConsoleColor_DarkGrey : ConsoleColor_Black;
            length = sprintf_s(buffer, getMenuItemName(i));
            x = SCREEN_WIDTH / 2 - length / 2;
            getRenderSystem()->drawText(x, y + i * 2, buffer, ConsoleColor_White, background);
        }
    }

    void update(float dt)
    {
        if (isKeyDown(VK_DOWN) && m_KeyPressCooldown <= 0)
        {
            if (m_selected < m_menuItems-1)
            {
                m_selected++;
            }
            else
            {
                m_selected = 0;
            }
            m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
        }
        if (isKeyDown(VK_UP) && m_KeyPressCooldown <= 0)
        {
            if (m_selected > 0)
            {
                m_selected--;
            }
            else
            {
                m_selected = m_menuItems-1;
            }
            m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
        }
        if (isKeyDown(VK_RETURN) && m_KeyPressCooldown <= 0)
        {
            close();
            m_KeyPressCooldown = KEY_PRESS_COOLDOWN;
        }

        if (m_KeyPressCooldown > 0)
        {
            m_KeyPressCooldown -= dt;
        }
    }
private:
    const float KEY_PRESS_COOLDOWN = .3;
    int m_selected;
    int m_menuItems;
    float m_KeyPressCooldown;

    const char* getMenuItemName(int item)
    {
        switch (item)
        {
        case 0: return "1 Player";
        case 1: return "2 Players";
        }
        return "";
    }
};

class LevelDivider : public Screen
{
public:
    LevelDivider() : Screen(3) {}

protected:
    const char* getText()
    {
        if (getRemainedTime() > 2)
        {
            return "Ready?";
        }
        else if (getRemainedTime() > 1)
        {
            return "Set...";
        }
        else
        {
            return "Go!";
        }
    }

    void render()
    {
        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "Level completed!");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 - 1, buffer, ConsoleColor_White, ConsoleColor_Black);

        length = sprintf_s(buffer, getText());
        x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 + 1, buffer, ConsoleColor_White, ConsoleColor_Black);
    }
};

class GameOver : public Screen
{
public:
    GameOver(Player* player1, Player* player2) : Screen()
    {
        m_player1 = player1;
        m_player2 = player2;
    }
    
protected:
    void render()
    {
        char buffer[SCREEN_WIDTH];
        int length = sprintf_s(buffer, "GAME OVER");
        int x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 - 2, buffer, ConsoleColor_White, ConsoleColor_Black);

        int players = m_player2 == 0 ? 1 : 2;
        if (players == 1)
        {
            length = sprintf_s(buffer, "Your score: %d", m_player1->getScore());
            x = SCREEN_WIDTH / 2 - length / 2;
            getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
        }
        else
        {
            length = sprintf_s(buffer, "Player 1 score: %d", m_player1->getScore());
            x = SCREEN_WIDTH / 2 - length / 2;
            getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);

            length = sprintf_s(buffer, "Player 2 score: %d", m_player2->getScore());
            x = SCREEN_WIDTH / 2 - length / 2;
            getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 + 2, buffer, ConsoleColor_Grey, ConsoleColor_Black);
        }

        length = sprintf_s(buffer, "Press 'Q' to exit...");
        x = SCREEN_WIDTH / 2 - length / 2;
        getRenderSystem()->drawText(x, SCREEN_HEIGHT / 2 + players * 3, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }

    void update(float dt)
    {
        if (isKeyDown('Q'))
        {
            close();
        }
    }

private:
    Player* m_player1;
    Player* m_player2;

};
