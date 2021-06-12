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

////////////////////////////////////////////////////////////////////////////
int widthX = 800;
int widthY = 800;
////////////////////////////////////////////////////////////////////////////

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit()) { return -1; }

	window = glfwCreateWindow(widthX, widthY, "WindowTitle", /*glfwGetPrimaryMonitor()*/NULL, NULL);
	if (!window){ glfwTerminate(); return -1; }

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glViewport(0, 0, widthX, widthY);

	if (glewInit() != GLEW_OK)
		std::cout << "Something went wrong in GLEW init" << std::endl;

    {
		int l = 250;
		std::vector<vect2f> points;
		for (int i = 0; i < l; i++)
		{
			float x = -1.0+1.0/l*(l-i);
			float y = 1.;
			points.push_back({x, y});
		}
		
		Chain chain(points, 1.0/l, 5.0, 1.);

		// // Timing stuff;
		std::chrono::steady_clock::time_point current_time 
			= std::chrono::steady_clock::now();
		float dt = std::chrono::duration_cast<std::chrono::microseconds>
						(std::chrono::steady_clock::now() - current_time).count();
		float t = 0.;

		float DT = 0.05; // Testing purposes. 

       	while (!glfwWindowShouldClose(window))
		{
			dt = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()-current_time).count();
			current_time = std::chrono::steady_clock::now();

			t += dt / 1000000.0; // t in seconds;
			dt = dt / 1000000.0; // dt in seconds;

			std::cout << 1/dt << " FPS.\n";

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			chain.Update(dt);
			chain.Draw();

			GLCall( glfwSwapBuffers(window) );
			GLCall( glfwPollEvents() );
		}
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