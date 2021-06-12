#include "App.h" 

App::App(unsigned int widthX, unsigned int widthY, char* title)
{
    if (!glfwInit()) 
    {
        error = true;
        errorMsg = "App: GLFW initialisation error.";
        return; 
    }

    m_window = glfwCreateWindow(m_widthX, m_widthX, title, NULL, NULL);

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);
	glViewport(0, 0, m_widthX, m_widthY);

    if (glewInit() != GLEW_OK)
    {
        error = true;
        errorMsg = "App: GLEW initialisation error.";
        return;
    }
}

App::~App()
{
    glfwTerminate();
}

float App::dt()
{
    return std::chrono::duration_cast<std::chrono::microseconds> (chr::now() - m_CurrentTime).count();
}