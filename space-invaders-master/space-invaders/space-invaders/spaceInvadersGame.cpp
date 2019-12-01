#include "spaceInvadersGame.h"
#include "spaceInvadersObjects.h"
#include "spaceInvadersScreens.h"
#include <cmath>

const float LEVEL_RESTART_COOLDOWN = 2;

GameObject* CreateGameObject(unsigned char symbol)
{
    switch (symbol)
    {
    case CellSymbol_Player:
        return new Player(3, SHIP_FIRE_COOLDOWN);
    case CellSymbol_Alien:
        return new Alien(1, 5);
    case CellSymbol_AlienSpread:
        return new Alien(2, 7);
    case CellSymbol_AlienBrood:
        return new Alien(3, 10);
    case CellSymbol_AlienTank:
        return new Alien(5, 11);
    }
    return 0;
}

void SpaceInvaders::initialize()
{
    if (getCurrentLevel() > 0)
    {
        LevelDivider* divider = new LevelDivider();
        divider->show();
        delete divider;
    }

    Game::initialize();

    Player* saved1 = m_player1;
    Player* saved2 = m_player2;
    m_player1 = 0;
    m_player2 = 0;
    m_alienAmplitudeTime = 0.0;
    m_freezeAliensTime = 0;
    m_alienFireCooldown = ALIEN_FIRE_COOLDOWN - (getCurrentLevel() * 0.23);
    m_restartLevelCooldown = LEVEL_RESTART_COOLDOWN;

    LevelData levelData = getLevel()->getLevelData(getCurrentLevel());
    for (int row = 0; row < levelData.size(); row++)
    {
        for (int col = 0; col < levelData[row].size(); col++)
        {
            const unsigned char symbol = levelData[row][col];
            switch (symbol)
            {
            case CellSymbol_Player:
            {
                Player* player1 = (Player*)initializeObject(CreateGameObject(symbol), GameObjectType_Ship, col + 0.5, row,
                    getLevel()->getRenderCellSymbol(symbol),
                    getLevel()->getRenderCellSymbolColor(symbol),
                    getLevel()->getRenderCellSymbolBackgroundColor(symbol));
                setPlayer1((Player*)player1);
                if (saved1 != 0)
                {
                    player1->setScore(saved1->getScore());
                }

                if (m_players > 1)
                {
                    Player* player2 = (Player*)initializeObject(CreateGameObject(symbol), GameObjectType_Ship, col + 0.5, row,
                        getLevel()->getRenderCellSymbol(symbol),
                        getLevel()->getRenderCellSymbolColor(symbol),
                        getLevel()->getRenderCellSymbolBackgroundColor(symbol));
                    setPlayer2(player2);
                    if (saved2 != 0)
                    {
                        player2->setScore(saved2->getScore());
                    }

                    player1->setX(player1->getX() - 1);
                    player2->setX(player2->getX() + 1);

                    player1->setBackgroundColor(ConsoleColor_DarkBlue);
                    player2->setBackgroundColor(ConsoleColor_DarkYellow);
                }

                break;
            }
            case CellSymbol_Alien:
            case CellSymbol_AlienSpread:
            case CellSymbol_AlienBrood:
            case CellSymbol_AlienTank:
            {
                Alien* alien = (Alien*)initializeObject(CreateGameObject(symbol), GameObjectType_Alien, col + 0.5, row,
                    getLevel()->getRenderCellSymbol(symbol),
                    getLevel()->getRenderCellSymbolColor(symbol),
                    getLevel()->getRenderCellSymbolBackgroundColor(symbol));
                alien->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
                alien->setYSpeed(ALIEN_SPEED);
                if (m_players > 1)
                {
                    alien->setStrength(alien->getStrength() * m_players);
                }
                break;
            }
            }
        }
    }
}

void SpaceInvaders::render()
{
    Game::render();

    char buffer[SCREEN_WIDTH];
    int length = 0;
    int startX = 0;

    length = sprintf_s(buffer, "Level: %d  ", getCurrentLevel() + 1);
    getRenderSystem()->drawText(startX, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    startX += length;
    
    if (m_players > 1)
    {
        length = sprintf_s(buffer, "P1: ");
        getRenderSystem()->drawText(startX, 0, buffer, ConsoleColor_Blue, ConsoleColor_Black);
        startX += length;
    }

    for (int i = 0; i < getPlayer1()->getStrength(); i++)
    {
        getRenderSystem()->drawChar(startX, 0, 3, ConsoleColor_DarkRed, ConsoleColor_Black);
        startX += 2;
    }
    length = sprintf_s(buffer, "Score: %d", getPlayer1()->getScore());
    getRenderSystem()->drawText(++startX, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    startX += length;

    if (m_players > 1)
    {
        startX++;
        length = sprintf_s(buffer, "P2: ");
        getRenderSystem()->drawText(startX, 0, buffer, ConsoleColor_Yellow, ConsoleColor_Black);
        startX += length;

        for (int i = 0; i < getPlayer2()->getStrength(); i++)
        {
            getRenderSystem()->drawChar(startX, 0, 3, ConsoleColor_DarkRed, ConsoleColor_Black);
            startX += 2;
        }
        sprintf_s(buffer, "Score: %d", getPlayer2()->getScore());
        getRenderSystem()->drawText(++startX, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
    }
}

void SpaceInvaders::update(float dt)
{
    if (getPlayer1()->getStrength() > 0)
    {
        if (isKeyDown(VK_LEFT))
        {
            getPlayer1()->setXSpeed(-SHIP_SPEED);
        }
        else if (isKeyDown(VK_RIGHT))
        {
            getPlayer1()->setXSpeed(SHIP_SPEED);
        }
        if (isKeyDown(VK_UP) && getPlayer1()->getFireCooldown() <= 0)
        {
            getPlayer1()->updateFireCooldown();
            GameObject* bullet = initializeObject(new Bullet(getPlayer1()), GameObjectType_Bullet,
                getPlayer1()->getX(), getPlayer1()->getY() - 1,
                getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
                getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
                getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
            bullet->setYSpeed(-BULLET_SPEED);
            
            if (getPlayer1()->isBonusDoubleFire())
            {
                GameObject* bullet2 = initializeObject(new Bullet(getPlayer1()), GameObjectType_Bullet,
                    getPlayer1()->getX(), getPlayer1()->getY() - 1,
                    getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
                    getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
                    getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
                bullet2->setYSpeed(-BULLET_SPEED);
                
                bullet->setX(bullet->getX() - 1);
                bullet2->setX(bullet->getX() + 1);
            }
        }
    }
    if (m_players > 1 && getPlayer2()->getStrength() > 0)
    {
        if (isKeyDown('A'))
        {
            getPlayer2()->setXSpeed(-SHIP_SPEED);
        }
        else if (isKeyDown('D'))
        {
            getPlayer2()->setXSpeed(SHIP_SPEED);
        }
        if (isKeyDown('W') && getPlayer2()->getFireCooldown() <= 0)
        {
            getPlayer2()->updateFireCooldown();
            GameObject* bullet = initializeObject(new Bullet(getPlayer2()), GameObjectType_Bullet,
                getPlayer2()->getX(), getPlayer2()->getY() - 1,
                getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
                getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
                getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
            bullet->setYSpeed(-BULLET_SPEED);
            if (getPlayer2()->isBonusDoubleFire())
            {
                GameObject* bullet2 = initializeObject(new Bullet(getPlayer2()), GameObjectType_Bullet,
                    getPlayer2()->getX(), getPlayer2()->getY() - 1,
                    getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
                    getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
                    getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
                bullet2->setYSpeed(-BULLET_SPEED);

                bullet->setX(bullet->getX() - 1);
                bullet2->setX(bullet->getX() + 1);
            }
        }
    }

    if (isKeyDown('N') && m_restartLevelCooldown <= 0.0)
    {
        nextLevelOrEnd();
    }
    else if (m_restartLevelCooldown > 0)
    {
        m_restartLevelCooldown -= dt;
    }
    
    bool haveAliveAliens = false;

    for (int i = 0; i < getObjects().size(); i++)
    {
        GameObject* object = getObjects()[i];
        if (isDeleted(object))
        {
            continue;
        }

        if (!(m_freezeAliensTime > 0 && object->getType() == GameObjectType_Alien)) {
            object->update(dt);
        }
        switch (object->getType())
        {
        case GameObjectType_Alien:
        {
            Alien* alien = (Alien*)object;
            haveAliveAliens = true;
            if (alien->getY() >= LEVEL_ROWS)
            {
                setGameActive(false);
            }
            else if(m_freezeAliensTime <= 0)
            {
                alien->setXSpeed(ALIEN_AMPLITUDE * cos(m_alienAmplitudeTime));
            }
            break;
        }
        case GameObjectType_Bullet:
            if (object->getY() < 0 || object->getY() > SCREEN_HEIGHT)
            {
                planDelete(object);
            }
            else
            {
                for (int a = 0; a < getObjects().size(); a++)
                {
                    GameObject* subject = getObjects()[a];
                    if (isDeleted(subject))
                    {
                        continue;
                    }
                    if (object != subject && object->intersects(subject))
                    {
                        Bullet* bullet = (Bullet*)object;

                        if (subject->getType() == GameObjectType_Alien && bullet->getShooter()->getType() == GameObjectType_Ship) {
                            Alien* alien = (Alien*)subject;
                            Player* player = (Player*)bullet->getShooter();

                            if (alien->tryKill())
                            {
                                player->addScore(alien->getWorth());
                                planDelete(alien);

                                if (rand() % 1000 <= BOUNS_FAST_RELOAD_CHANCE)
                                {
                                    GameObject* bonus = initializeObject(new GameObject(), GameObjectType_FastReload,
                                        alien->getX(),
                                        alien->getY(),
                                        'R',
                                        ConsoleColor_Blue,
                                        ConsoleColor_Black);
                                    bonus->setYSpeed(BONUS_SPEED);
                                }
                                else if (rand() % 1000 <= BONUS_DOUBLE_FIRE_CHANCE)
                                {
                                    GameObject* bonus = initializeObject(new GameObject(), GameObjectType_DoubleFire,
                                        alien->getX(),
                                        alien->getY(),
                                        'D',
                                        ConsoleColor_Red,
                                        ConsoleColor_Black);
                                    bonus->setYSpeed(BONUS_SPEED);
                                }
                                else if (rand() % 1000 <= BONUS_FREEZE_CHANCE)
                                {
                                    GameObject* bonus = initializeObject(new GameObject(), GameObjectType_Freeze,
                                        alien->getX(),
                                        alien->getY(),
                                        'F',
                                        ConsoleColor_Cyan,
                                        ConsoleColor_Black);
                                    bonus->setYSpeed(BONUS_SPEED);
                                }
                            }
                            planDelete(bullet);
                        }
                        else if (subject->getType() == GameObjectType_Ship && bullet->getShooter()->getType() == GameObjectType_Alien)
                        {
                            Player* player = (Player*)subject;
                            Alien* alien = (Alien*)bullet->getShooter();

                            if (player->tryKill())
                            {
                                planDelete(player);
                                if (m_players == 1)
                                {
                                    setGameActive(false);
                                }
                                else if (getPlayer1()->getStrength() <= 0 && getPlayer2()->getStrength() <= 0)
                                {

                                    setGameActive(false);
                                }
                            }
                            planDelete(bullet);
                        }
                        break;
                    }
                }
            }
            break;

        case GameObjectType_FastReload:
        {
            Player* player1 = getPlayer1();
            Player* player2 = getPlayer2();

            if (object->intersects(player1))
            {
                player1->applyBonusFastReload();
                planDelete(object);
            }
            else if (player2 != 0 && object->intersects(player2))
            {
                player2->applyBonusFastReload();
                planDelete(object);
            }
            else if (object->getY() > SCREEN_HEIGHT)
            {
                planDelete(object);
            }
            break;
        }
        case GameObjectType_DoubleFire:
        {
            Player* player1 = getPlayer1();
            Player* player2 = getPlayer2();

            if (object->intersects(player1))
            {
                player1->applyBonusDoubleFire();
                planDelete(object);
            }
            else if (player2 != 0 && object->intersects(player2))
            {
                player2->applyBonusDoubleFire();
                planDelete(object);
            }
            else if (object->getY() > SCREEN_HEIGHT)
            {
                planDelete(object);
            }
            break;
        }
        case GameObjectType_Freeze:
        {
            Player* player1 = getPlayer1();
            Player* player2 = getPlayer2();

            if (object->intersects(player1) || (player2 != 0 && object->intersects(player2)))
            {
                m_freezeAliensTime = BONUS_FREEZE_TIME;
                planDelete(object);
            }
            else if (object->getY() > SCREEN_HEIGHT)
            {
                planDelete(object);
            }

            break;
        }
        }
    }

    if (m_freezeAliensTime <= 0)
    {
        m_alienAmplitudeTime += dt;
    }
    if (m_alienFireCooldown > 0)
    {
        m_alienFireCooldown -= dt;
    }
    else if (haveAliveAliens) {
        int index = rand() % getObjects().size();
        while (getObjects()[index]->getType() != GameObjectType_Alien)
        {
            index++;
            if (index >= getObjects().size())
            {
                index = 0;
            }
        }
        GameObject* alien = getObjects()[index];
        GameObject* bullet = initializeObject(new Bullet(alien), GameObjectType_Bullet,
            alien->getX(), alien->getY() + 1,
            getLevel()->getRenderCellSymbol(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolColor(CellSymbol_Bullet),
            getLevel()->getRenderCellSymbolBackgroundColor(CellSymbol_Bullet));
        bullet->setYSpeed(BULLET_SPEED);
        m_alienFireCooldown = ALIEN_FIRE_COOLDOWN;
    }
    if (m_freezeAliensTime > 0)
    {
        m_freezeAliensTime -= dt;
    }

    if (!haveAliveAliens)
    {
        nextLevelOrEnd();
    }
}
