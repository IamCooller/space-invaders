#pragma once

#include "renderSystem.h"

typedef int GameObjectType;

const GameObjectType GameObjectType_None = -1;

class GameObject
{
public:
    GameObject();

    virtual void render(RenderSystem* rs);
    virtual void update(float dt);

    virtual bool intersects(GameObject* object);

    void setType(GameObjectType type) { m_type = type; }
    GameObjectType getType() { return m_type; }

    void setX(float x) { m_x = x; }
    float getX() { return m_x; }

    void setY(float y) { m_y = y; }
    float getY() { return m_y; }

    void setXSpeed(float speed) { m_xSpeed = speed; }
    float getXSpeed() { return m_xSpeed; }

    void setYSpeed(float speed) { m_ySpeed = speed; }
    float getYSpeed() { return m_ySpeed; }

    void setSymbol(unsigned char symbol) { m_symbol = symbol; }
    unsigned char getSymbol() { return m_symbol; }

    void setColor(ConsoleColor color) { m_color = color; }
    ConsoleColor getColor() { return m_color; }

    void setBackgroundColor(ConsoleColor color) { m_backgroundColor = color; }
    ConsoleColor getBackgroundColor() { return m_backgroundColor; }

private:
    GameObjectType m_type;

    float m_x;
    float m_y;
    float m_xSpeed;
    float m_ySpeed;
    
    unsigned char m_symbol;
    ConsoleColor m_color;
    ConsoleColor m_backgroundColor;
};