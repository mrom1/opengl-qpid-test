#pragma once
#include "Square.hpp"

#include <GL/glut.h>
#include <memory>

class Window
{
public:
    Window() : mWindowHeight(400), mWindowWidth(400)
    {

    }

    void Initialize(int argc, char *argv[])
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(mWindowWidth, mWindowHeight);
        glutInitWindowPosition(200, 200);
        glutCreateWindow("OpenGL Demonstrator");

        glutMotionFunc(drag);

        glClearColor(0.0, 0.0, 0.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

        glutDisplayFunc(display);
        glutMainLoop();
    }

    void createSquare(float diameter, float startPosition)
    {
        mDataModel = std::make_shared<Square>(diameter, startPosition);
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        mDataModel->draw();
        glFlush();
    }

    Points mouse(int x, int y)
    {
        return Points(float(x) / windowWidth, 1.0 - float(y) / windowHeight);
    }

    void drag(int x, int y)
    {
        // int x and y of mouse converts to screen coordinates
        // returns the point as mousePt
        Points mousePt = mouse(x, y);
        if(mDataModel->isInsideGeometry(mousePt.x, mouesPt.y))
        {
            mDataModel->drag(mousePt.x, mousePt.y);
            glutPostRedisplay();
        }
    }

private:
    std::shared_ptr<Square> mDataModel;
    int mWindowWidth, mWindowHeight;
};