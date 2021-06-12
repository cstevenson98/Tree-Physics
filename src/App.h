#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <string> 

using chr = std::chrono::steady_clock;

class App
{
private:
    GLFWwindow* m_window;

    unsigned int m_widthX;
    unsigned int m_widthY;

    // Global timing information
    chr::time_point m_CurrentTime = chr::now();
    
public:
    App(unsigned int widthX, unsigned int widthY, char* title);
    ~App();

    float dt();

    bool error = false;
    std::string errorMsg;
};