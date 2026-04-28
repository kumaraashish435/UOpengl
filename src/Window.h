#pragma once

#include "Application.h"

class Window
{
public:
    Window();
    ~Window();

    bool ShouldClose() const;
    void Update();
    void Clear(float r, float g, float b, float a);
    void processInput();

private:
    GLFWwindow* m_Window;
    int WIDTH = 800, HEIGHT = 800;
};