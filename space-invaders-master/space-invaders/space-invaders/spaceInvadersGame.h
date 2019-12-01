#pragma once

#include "game.h"
#include "spaceInvadersObjects.h"

class SpaceInvaders : public Game
{
public:
    SpaceInvaders(int players) : Game()
    {
        m_players = players;
    }

    void initialize();

    void setPlayer1(Player* player) { m_player1 = player; }
    Player* getPlayer1() { return m_player1; }

    void setPlayer2(Player* player) { m_player2 = player; }
    Player* getPlayer2() { return m_player2; }

protected:
    void render();
    void update(float dt);

private:
    int m_players;
    Player* m_player1 = 0;
    Player* m_player2 = 0;
    float m_alienAmplitudeTime;
    float m_alienFireCooldown;
    float m_restartLevelCooldown;
    float m_freezeAliensTime;
};
