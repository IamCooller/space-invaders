#pragma once

#include <ctime>
#include "renderSystem.h"

class Screen
{
public:
    Screen(int duration)
    {
        m_isInfinite = false;
        m_totalTime = duration;
        m_showDuration = duration;
    }
    Screen()
    {
        m_isInfinite = true;
        m_totalTime = 0;
        m_showDuration = 0;
    }

    void show();
    void close();

protected:
    virtual void render();
    virtual void update(float dt);

    float getTotalTime() { return m_totalTime; }
    float getRemainedTime() { return m_showDuration; }
    RenderSystem* getRenderSystem() { return &m_renderSystem; }

private:
    RenderSystem m_renderSystem;

    float m_totalTime;
    float m_showDuration;
    float m_isInfinite;
};
