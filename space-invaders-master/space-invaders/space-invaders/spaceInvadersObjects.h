#pragma once

#include "gameObject.h"
#include <cmath>

const float SHIP_SPEED = 35.0;
const float SHIP_FIRE_COOLDOWN = 0.2;

const float BULLET_SPEED = 40.0;

const float ALIEN_AMPLITUDE = 7.0;
const float ALIEN_SPEED = 0.18;
const float ALIEN_FIRE_COOLDOWN = 2.08;

const float BOUNS_FAST_RELOAD_CHANCE = 8;
const float BONUS_DOUBLE_FIRE_CHANCE = 6;
const float BONUS_FREEZE_CHANCE = 4;
const float BONUS_SPEED = 3;
const float BONUS_FAST_RELOAD_COOLDOWN = 0.02;
const float BONUS_FAST_RELOAD_TIME = 2.88;
const float BONUS_DOUBLE_FIRE_TIME = 2.33;
const float BONUS_FREEZE_TIME = 2.48;

const unsigned char CellSymbol_Player      = 'P';
const unsigned char CellSymbol_Bullet      = '|';
const unsigned char CellSymbol_Alien       = 'X';
const unsigned char CellSymbol_AlienSpread = 'S';
const unsigned char CellSymbol_AlienBrood  = 'B';
const unsigned char CellSymbol_AlienTank   = 'T';

enum SIObjectType : GameObjectType
{
    GameObjectType_Ship,
    GameObjectType_Bullet,
    GameObjectType_Alien,
    GameObjectType_FastReload,
    GameObjectType_DoubleFire,
    GameObjectType_Freeze
};

class Ship : public GameObject
{
public:
    Ship(int strength)
    {
        m_strength = strength;
    }

    void update(float dt)
    {
        GameObject::update(dt);
    }

    int getStrength() { return m_strength; }
    void setStrength(int strength) { m_strength = strength; }
    bool tryKill() { return ((--m_strength) <= 0); }

private:
    int m_strength;
};

class Player : public Ship
{
public:
    Player(int strength, float fireCooldown) : Ship(strength)
    {
        m_score = 0;
        m_fireCooldown = fireCooldown;
        m_currentFireCooldown = 0;
    }

    void update(float dt)
    {
        Ship::update(dt);
        if (getX() < 0)
        {
            setX(0);
        }
        else if (getX() > SCREEN_WIDTH - 1)
        {
            setX(SCREEN_WIDTH - 1);
        }
        if (m_fireCooldown > 0)
        {
            m_currentFireCooldown -= dt;
        }
        if (m_bonusReloadTime > 0)
        {
            m_bonusReloadTime -= dt;
        }
        if (m_bonusDoubleFireTime > 0)
        {
            m_bonusDoubleFireTime -= dt;
        }
    }

    void applyBonusFastReload() { m_bonusReloadTime = BONUS_FAST_RELOAD_TIME; }
    void applyBonusDoubleFire() { m_bonusDoubleFireTime = BONUS_DOUBLE_FIRE_TIME; }
    bool isBonusDoubleFire() { return m_bonusDoubleFireTime > 0; }

    int getScore() { return m_score; }
    void setScore(int score) { m_score = score; }
    void addScore(int score) { m_score += score; }

    float getFireCooldown() { return m_currentFireCooldown; }
    void updateFireCooldown()
    {
        m_currentFireCooldown = m_bonusReloadTime > 0 ? BONUS_FAST_RELOAD_COOLDOWN : m_fireCooldown;
    }

private:
    int m_score;
    float m_fireCooldown;
    float m_currentFireCooldown;
    float m_bonusReloadTime;
    float m_bonusDoubleFireTime;
};

class Alien : public Ship
{
public:
    Alien(int strength, int worth) : Ship(strength)
    {
        m_worth = worth;
    }

    int getWorth() { return m_worth; }

private:
    int m_worth;
};

class Bullet : public GameObject
{
public:
    Bullet(GameObject* shooter) : GameObject()
    {
        m_shooter = shooter;
    }

    GameObject* getShooter() { return m_shooter; }

private:
    GameObject* m_shooter;
};
