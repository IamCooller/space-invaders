#include "game.h"
#include <cstdlib>
#include <algorithm>

void Game::setupSystem()
{
    srand(time(0));
    m_isGameActive = true;
    m_isLevelEnd = false;
    m_currentLevel = 0;
    m_renderSystem.initialize();
}

void Game::initialize()
{
    m_renderSystem.forceClear();
    m_isLevelEnd = false;

    m_clockLastFrame = clock();
    m_framesCounter = 0;
    m_framesTimeCounter = 0;
    m_fps = 0;

    m_objects.clear();
    m_subjectsForDeletion.clear();
}

bool Game::frame()
{
    clock_t clockNow = clock();
    clock_t deltaClock = clockNow - m_clockLastFrame;
    float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
    m_clockLastFrame = clockNow;

    m_framesCounter++;
    m_framesTimeCounter += deltaTime;
    if (m_framesTimeCounter >= 1.0)
    {
        m_framesTimeCounter -= 1.0;
        m_fps = m_framesCounter;
        m_framesCounter = 0;
    }

    m_renderSystem.clear();
    render();
    m_renderSystem.flush();
    update(deltaTime);
    //delete planned objects
    if (m_subjectsForDeletion.size() > 0)
    {
        for (int i = 0; i < m_subjectsForDeletion.size(); i++)
        {
            destroyObject(m_subjectsForDeletion[i]);
        }
        m_subjectsForDeletion.clear();
    }
    if (m_isLevelEnd)
    {
        m_currentLevel++;
        m_isLevelEnd = false;
        if (m_level.getLevelData(m_currentLevel) == levelDataEmpty)
        {
            m_isGameActive = false;
        }
        else
        {
            initialize();
        }
    }

    return m_isGameActive;
}

void Game::shutdown()
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        delete m_objects[i];
    }
    m_objects.clear();
    m_renderSystem.clear();
    m_renderSystem.flush();
}

void Game::render()
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->render(&m_renderSystem);
    }

    char buffer[SCREEN_WIDTH];
    int length = sprintf_s(buffer, "FPS: %d", getFps());
    m_renderSystem.drawText(SCREEN_WIDTH - length, 0, buffer, ConsoleColor_Grey, ConsoleColor_Black);
}

void Game::update(float dt)
{
    for (int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update(dt);
    }
}

GameObject* Game::initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor)
{
    m_objects.push_back(object);

    object->setType(type);
    object->setX(x);
    object->setY(y);
    object->setSymbol(symbol);
    object->setColor(color);
    object->setBackgroundColor(backgroundColor);

    return object;
}

void Game::destroyObject(GameObject* object)
{
    m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Game::nextLevelOrEnd()
{
    m_isLevelEnd = true;
}
