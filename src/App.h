#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <string> 
#include <iostream>

using chr = std::chrono::steady_clock;

namespace App
{
    void init(GLFWwindow** window, int widthX, int widthY, std::string title);

    class Timer 
    {
    public:
        chr::time_point m_CurrentTime;

        Timer()
        : m_CurrentTime( chr::now() )
        { }

        ~Timer()
        { }

        float dt();
    };

} // namespace App
