#pragma once




#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

#include "openGLutils.h"
#include "linear.h"

class Chain
{
public:
    float m_dist;
    float m_g;
    std::vector<vect2f> m_present;
    std::vector<vect2f> m_past;
    std::vector<float> m_XY;

    float m_drag;
    GLuint m_vb;
    Shader m_shader;

    int m_LineWidth = 1;
    int m_PointSize = 4;

    Chain() 
    : m_dist(1.), 
      m_g(1.), 
      m_drag(0.9995) 
    { }
    
    Chain(std::vector<vect2f> &init, float dist, float g, float drag)
    : m_present(init), 
      m_past(init), 
      m_dist(dist), 
      m_g(g), 
      m_drag(drag),
      m_shader(Shader("shaders/Basic.shader"))
    { 
        FlattenState();
        glGenBuffers(1, &m_vb);
        glBindBuffer(GL_ARRAY_BUFFER, m_vb);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
        
        m_shader.Bind();
    }

    ~Chain() 
    { }

    float* XYData();
    void Update(float dt);
    void Draw();
    void FlattenState();
};
