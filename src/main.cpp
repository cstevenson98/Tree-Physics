#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <cassert>
//#include <chrono>

// #include "trees.h"
#include "openGLutils.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <numeric>
#include <math.h>
#include <chrono>

#include "Chain.h"
#include "linear.h"
#include "App.h"

////////////////////////////////////////////////////////////////////////////
unsigned int widthX = 1000;
unsigned int widthY = 1000;
std::string title = "Verlet integration";
////////////////////////////////////////////////////////////////////////////

double xPos = 0.;
double yPos = 0.;
double mouseX = 0.;
double mouseY = 0.;

bool clicked = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W)
        yPos += 0.025;
	if (key == GLFW_KEY_S)
        yPos -= 0.025;
	if (key == GLFW_KEY_D)
        xPos += 0.025;
	if (key == GLFW_KEY_A)
        xPos -= 0.025;

}

void mouse_callback(GLFWwindow* window, double _xPos, double _yPos)
{
    mouseX = _xPos;
	mouseY = _yPos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		xPos = -1 + 2*mouseX/widthX;
		yPos = 1 - 2*mouseY/widthY;
		clicked = true;
	}
}

int main(void)
{
	// Initialise GLFW window
	GLFWwindow* window;
	App::init(&window, widthX, widthY, title);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback( window, mouse_callback );
	glfwSetMouseButtonCallback( window, mouse_button_callback );

	// Initialise a chain physics object pinned at (0, 1):
	int l = 1551;
	std::vector<vect2f> points;
	for (int i = 0; i < l; i++)
	{
		float x = -1.0 + 2.0/l * (l-i);
		float y = 0.;
		points.push_back({x, y});
	}
	Chain chain(points, 1./l, .4, 1.0);

	// Main loop with timer to track frame times
	App::Timer timer;
	float t = 0;
    while (!glfwWindowShouldClose(window))
	{
		// std::cout << "Hello" << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		float dt = timer.dt();
		t += dt;

		chain.Update(dt);

		if(clicked)
		{
			chain.m_present[l/2].x = xPos;
			chain.m_present[l/2].y = yPos;
			clicked = false;
		}
		chain.m_present[l-1].x = -1.;
		chain.m_present[l-1].y = 0.;
		chain.Draw();

		GLCall( glfwSwapBuffers(window) );
		GLCall( glfwPollEvents() );
	}
	
	return 0;
}

// Tree code need verlet integration first

// int depth = 6; int order = 3;
// 		vect2f x0 = {-1., 0.};
// 		vect2f n0 = { 1, 0. };
// 		std::vector<float> thetas = { -0.3, 0., 0.3 };
// 		std::vector<float> scales = { 0., 0.5 , 0.1 , 0.05, 0.025, 0.01, 0.001 };
	
// 		Map myMap0 = { { "1", "11" }, { "1", "12" }, { "1", "13" }};
// 		mapBuild(myMap0, depth, order);
// 		printMap(myMap0);
		
// 		/////////////////////////////////////

// 		std::vector<float> store;
// 		store.push_back(x0.x);
// 		store.push_back(x0.y);
// 		store.push_back(x0.x + n0.x);
// 		store.push_back(x0.y + n0.y);
// 		for (auto &i : myMap0)
// 		{
// 			treeStr2Vect2f(n0, scales, thetas, i.first).print();
// 			store.push_back(x0.x + n0.x + treeStr2Vect2f(n0, scales, thetas, i.first).x);
// 			store.push_back(x0.y + n0.y + treeStr2Vect2f(n0, scales, thetas, i.first).y);
// 			store.push_back(x0.x + n0.x + treeStr2Vect2f(n0, scales, thetas, i.second).x);
// 			store.push_back(x0.y + n0.y + treeStr2Vect2f(n0, scales, thetas, i.second).y);
// 		}

// 		size_t treeBufferSize = store.size() * sizeof(float);

// 		/////////////////////////////////////
// 		// These are the points: connected in pairs
		
// 		float points[8] = { 0., 0.,
// 							0., 1., 
// 							1., 1., 
// 							0., -0.5 };

// 		GLuint vb;
// 		glGenBuffers(1, &vb);
// 		glBindBuffer(GL_ARRAY_BUFFER, vb);
// 		glBufferData(GL_ARRAY_BUFFER, treeBufferSize, store.data(), GL_STATIC_DRAW);

// 		glEnableVertexAttribArray(0);
//     	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);