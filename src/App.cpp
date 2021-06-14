#include "App.h"
#include <string>

void App::init(GLFWwindow** window, int widthX, int widthY, std::string title)
{
    glfwInit();
    *window = glfwCreateWindow(widthX, widthY, title.data(), NULL, NULL);
	if (!window)
	{ 
		std::cout << "Something went wrong in GLFW3 init" << std::endl; 
		glfwTerminate(); 
	}

	glfwMakeContextCurrent(*window);
	glfwSwapInterval(1);
	glViewport(0, 0, widthX, widthY);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Something went wrong in GLEW init" << std::endl;
}

float App::Timer::dt()
{
	float out_dt = std::chrono::duration_cast<std::chrono::microseconds>(chr::now() - m_CurrentTime).count();
	m_CurrentTime = chr::now();
	return out_dt / 1000000.0;
}