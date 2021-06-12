#include "Chain.h"

void Chain::FlattenState()
{
    m_XY.clear();
    for (auto &vec : m_present)
    {
        m_XY.push_back(vec.x);
        m_XY.push_back(vec.y);
    }
}

void Chain::Draw()
{
    // Put data into
    FlattenState();     
    glBufferData(GL_ARRAY_BUFFER, m_XY.size()*sizeof(float), m_XY.data(), GL_DYNAMIC_DRAW);

    glLineWidth(m_LineWidth);
    glPointSize(m_PointSize);
    glDrawArrays(GL_LINE_STRIP, 0, m_XY.size()/2);
    //glDrawArrays(GL_POINTS, 0, m_XY.size()/2);

}

void Chain::Update(float dt)
{
    std::vector<vect2f> store = m_present;

    // Apply external forces:
    for(int i = 1; i < m_present.size(); i++)
    {
        m_present[i].x = m_present[i].x + m_drag*(m_present[i].x - m_past[i].x);
        m_present[i].y = m_present[i].y + m_drag*(m_present[i].y - m_past[i].y) - m_g * dt * dt;
    }

    m_past = store;

    for(int j = 0; j < 600; j++)
    {
    for(int i = 1; i < m_present.size(); i++)
    {
        float dx = m_present[i].x - m_present[i-1].x;
        float dy = m_present[i].y - m_present[i-1].y;
        float d2 = sqrt(dx*dx + dy*dy);
        float diff = d2 - m_dist;
        float percent = diff/d2/2;
        float offx = dx*percent;
        float offy = dy*percent;

        m_present[i].x -= offx;
        m_present[i].y -= offy;
        
        if(i-1>0)
        {
            m_present[i-1].x += offx;
            m_present[i-1].y += offy;
        }
    }
    }
}