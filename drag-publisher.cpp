#include <GL/glut.h>
#include <iostream>

#include <qpid/messaging/Address.h>
#include <qpid/messaging/Connection.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Message_io.h>
#include <qpid/messaging/Sender.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Session.h>
#include <qpid/types/Variant.h>

using namespace qpid::messaging;
using namespace qpid::types;

Sender sender;

// points structure made of two coordinates; x and y
struct Points
{
    float x, y; // initializor
    Points()
    {
        x = 0.0;
        y = 0.0;
    } // constructor

    Points(float _x, float _y) : x(_x), y(_y) {}
};

// square made of 4 points
class Square
{
public:
    Points pts[4]; // square structure
    Square();      // initialize constructor

    void draw(Square *sqr);                   // draw square
    Points mouse(int x, int y);               // get mouse coordintaes
    Square *drag(Square *sqr, Points *mouse); // change points of sqr
};

// square constructor
Square::Square()
{
    pts[0] = Points(0.2, 0.2);
    pts[1] = Points(0.4, 0.2);
    pts[2] = Points(0.4, 0.4);
    pts[3] = Points(0.2, 0.4);
};

// draw function
void Square::draw(Square *sqr)
{
    // draw square fill
    int i;
    glColor3f(0.6, 0.8, 1.0);
    glBegin(GL_QUADS);
    for (i = 0; i < 4; ++i)
    {
        glVertex2f(sqr->pts[i].x, sqr->pts[i].y);
    }
    glEnd();
    // draw square points
    i = 0;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; ++i)
    {
        glVertex2f(sqr->pts[i].x, sqr->pts[i].y);
    }
    glEnd();
}

// mouse function
Points Square::mouse(int x, int y)
{
    int windowWidth = 400, windowHeight = 400;
    return Points(float(x) / windowWidth, 1.0 - float(y) / windowHeight);
}

void publish(float x, float y)
{
    try
    {
        Message msg;
        msg.getProperties()["mouse-x"] = x;
        msg.getProperties()["mouse-y"] = y;
        sender.send(msg);
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception in publish: " << e.what() << std::endl;
    }
}

// drag function
Square *Square::drag(Square *sqr, Points *mouse)
{
    sqr->pts[0].x = mouse->x - 0.1;
    sqr->pts[0].y = mouse->y - 0.1;

    sqr->pts[1].x = mouse->x + 0.1;
    sqr->pts[1].y = mouse->y - 0.1;

    sqr->pts[3].x = mouse->x - 0.1;
    sqr->pts[3].y = mouse->y + 0.1;

    sqr->pts[2].x = mouse->x + 0.1;
    sqr->pts[2].y = mouse->y + 0.1;

    std::cout << "Mouse: " << mouse->x << " X / " << mouse->y << " Y" << std::endl;
    publish(mouse->x, mouse->y);
    return sqr;
}

// GLOBAL

// create square object
Square *sqr = new Square;

// display at start
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    sqr->draw(sqr);
    glFlush();
}

// drag function
void drag(int x, int y)
{
    // int x and y of mouse converts to screen coordinates
    // returns the point as mousePt
    Points mousePt = sqr->mouse(x, y);
    //create pointer to window point coordinates
    Points *mouse = &mousePt;

    // if the mouse is within the square
    if (mouse->x > sqr->pts[0].x && mouse->y > sqr->pts[0].y)
    {
        if (mouse->x < sqr->pts[2].x && mouse->y < sqr->pts[2].y)
        {
            // then drag by chaning square coordinates relative to mouse
            sqr->drag(sqr, mouse);
            glutPostRedisplay();
        }
    }
}

void Initialize()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char **cppArgv)
{
    Connection connection("localhost:5672");
    connection.open();
    Session session = connection.createSession();

    sender = session.createSender("opengl-dragger; {create: always, node:{type: topic}}");


    glutInit(&iArgc, cppArgv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Dragging Example - Publisher");

    glutMotionFunc(drag);

    Initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
