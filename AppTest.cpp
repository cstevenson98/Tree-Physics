#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class App
{
public:
  GLFWwindow* m_window;

  App()
  {
    m_window = glfwCreateWindow(300, 300, "Test", NULL, NULL);
    glfwMakeContextCurrent(m_window);
    glfwInit();
  }

  ~App()
  {
    glfwTerminate();
  }
};

void init(GLFWwindow* window)
{
  glfwInit();
  window = glfwCreateWindow(100, 100, "WindowTitle", NULL, NULL);
	if (!window){ glfwTerminate(); }

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glViewport(0, 0, 100, 100);

	if (glewInit() != GLEW_OK)
		std::cout << "Something went wrong in GLEW init" << std::endl;

}

int main()
{
  //App app;
  GLFWwindow* window;
  init(window);
  std::cout << "App initialised!\n";
  return 0;
}
