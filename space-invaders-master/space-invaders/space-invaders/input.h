#pragma once

#include <Windows.h>

static bool isKeyDown(int virtualKeyCode)
{
    short keyState = GetAsyncKeyState(virtualKeyCode);
    return (keyState & 0x8000) > 0;
}


