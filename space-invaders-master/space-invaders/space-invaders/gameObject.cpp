#include "gameObject.h"

GameObject::GameObject()
{
    m_type = GameObjectType_None;

    m_x = 0;
    m_y = 0;

    m_xSpeed = 0;
    m_ySpeed = 0;

    m_symbol = '?';
    m_color = ConsoleColor_White;
    m_backgroundColor = ConsoleColor_Black;
}

void GameObject::render(RenderSystem* rs)
{
    int row = (m_y);
    int col = (m_x);

    rs->drawChar(col, row, m_symbol, m_color, m_backgroundColor);
}

void GameObject::update(float dt)
{
    m_x += m_xSpeed * dt;
    m_y += m_ySpeed * dt;
}

bool GameObject::intersects(GameObject* object)
{
    int row1 = int(m_y);
    int col1 = int(m_x);

    int row2 = int(object->m_y);
    int col2 = int(object->m_x);

    return row1 == row2 && col1 == col2;
}
