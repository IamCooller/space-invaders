#pragma once

#include <ctime>
#include <vector>
#include "renderSystem.h"
#include "gameObject.h"
#include "level.h"
#include "input.h"

class Game
{
public:
    virtual void setupSystem();
    virtual void initialize();
    virtual bool frame();
    virtual void shutdown();

    int getCurrentLevel() { return m_currentLevel; }
    void setCurrentLevel(int level) { m_currentLevel = level; }
    
    int getFps() { return m_fps; }

protected:
    virtual void render();
    virtual void update(float dt);

    GameObject* initializeObject(GameObject* object, GameObjectType type, float x, float y, char symbol, ConsoleColor color, ConsoleColor backgroundColor);
    void destroyObject(GameObject* object);

    bool isGameActive() { return m_isGameActive; }
    void setGameActive(bool active) { m_isGameActive = active; }

    RenderSystem* getRenderSystem() { return &m_renderSystem; }

    void nextLevelOrEnd();
    Level* getLevel() { return &m_level; }

    const std::vector<GameObject*> getObjects() { return m_objects; }
    void planDelete(GameObject* object) { m_subjectsForDeletion.push_back(object); }
    bool isDeleted(GameObject* object) { return std::find(m_subjectsForDeletion.begin(), m_subjectsForDeletion.end(), object) != m_subjectsForDeletion.end(); }
    
private:
    bool m_isGameActive;
    clock_t m_clockLastFrame;
    RenderSystem m_renderSystem;
    int m_currentLevel;
    bool m_isLevelEnd;
    Level m_level;
    std::vector<GameObject*> m_objects;
    std::vector<GameObject*> m_subjectsForDeletion;

    int m_framesCounter;
    float m_framesTimeCounter;
    int m_fps;
};
