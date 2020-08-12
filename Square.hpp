#pragma once

#include "serviceDrag.hpp"

#include "DataModel.h"
#include "Points.hpp"

#include <GL/glut.h>

class Square : public DataModel
{
public:
    Points pts[4]; // square structure
    Square(float _diameter, float _startPosition) : diameter(_diameter), startPosition(_startPosition)
    {
        pts[0] = Points(startPosition, startPosition);
        pts[1] = Points(startPosition + diameter, startPosition);
        pts[2] = Points(startPosition + diameter, startPosition + diameter);
        pts[3] = Points(startPosition, startPosition + diameter);
    }

    bool isInsideModel(float x, float y) override
    {
        if ((x > pts[0].x && y > pts[0]) && (x < pts[2].x && y < pts[2].y)) return true;
        else false;
    }

    void drag(float x, float y) override
    {
        pts[0].x = x - 0.1;
        pts[0].y = y - 0.1;
        pts[1].x = x + 0.1;
        pts[1].y = y - 0.1;
        pts[3].x = x - 0.1;
        pts[3].y = y + 0.1;
        pts[2].x = x + 0.1;
        pts[2].y = y + 0.1;
    }

    void draw() override
    {
        // draw square fill
        glColor3f(0.6, 0.8, 1.0);
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i)
        {
            glVertex2f(pts[i].x, pts[i].y);
        }
        glEnd();

        // draw square points
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_POINTS);
        for (int i = 0; i < 4; ++i)
        {
            glVertex2f(pts[i].x, pts[i].y);
        }
        glEnd();
    }

private:
    float diameter, startPosition;
};