#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>

// #include <iostream>
class wcPt2D
{
  public:
    GLfloat x, y;
    wcPt2D() { x = y = 0.0; }
    wcPt2D(float a, float b)
    {
        x = a;
        y = b;
    }
    void setCoords(GLfloat xCoord, GLfloat yCoord)
    {
        x = xCoord;
        y = yCoord;
    }
    GLfloat getx() const { return x; }
    GLfloat gety() const { return y; }
};

inline GLint round(const GLfloat a) { return GLint(a + 0.5); }

GLint clipTest(GLfloat p, GLfloat q, GLfloat *u1, GLfloat *u2)
{
    GLfloat r;
    GLint returnValue = true;
    if (p < 0.0)
    {
        r = q / p;
        if (r > *u2)
            returnValue = false;
        else if (r > *u1)
            *u1 = r;
    }
    else if (p > 0.0)
    {
        r = q / p;
        if (r < *u1)
            returnValue = false;
        else if (r < *u2)
            *u2 = r;
    }
    else
    {
        if (q < 0.0)
            returnValue = false;
    }
    return returnValue;
}

void drawLine(GLint x0, GLint y0, GLint x1, GLint y1)
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
}

void lineClipLiangBarsk(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
    GLfloat u1 = 0.0, u2 = 1.0, dx = p2.getx() - p1.getx(), dy;
    if (clipTest(-dx, p1.getx() - winMin.getx(), &u1, &u2))
    {
        if (clipTest(dx, winMax.getx() - p1.getx(), &u1, &u2))
        {
            dy = p2.gety() - p1.gety();
            if (clipTest(-dy, p1.gety() - winMin.gety(), &u1, &u2))
                if (clipTest(dy, winMax.gety() - p1.gety(), &u1, &u2))
                {
                    if (u2 < 1.0)
                    {
                        p2.setCoords(p1.getx() + u2 * dx, p1.gety() + u2 * dy);
                    }
                    if (u1 > 0.0)
                    {
                        p1.setCoords(p1.getx() + u1 * dx, p1.gety() + u1 * dy);
                    }
                    drawLine(round(p1.getx()), round(p1.gety()), round(p2.getx()),
                             round(p2.gety()));
                }
        }
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}
void triangle(wcPt2D *verts)
{
    GLint k;
    glBegin(GL_TRIANGLES);
    for (k = 0; k < 3; ++k)
    {
        glVertex2f(verts[k].x, verts[k].y);
    }
    glEnd();
}
void displayFcn()
{
    wcPt2D verts[3] = {{100.0, 100}, {500.0, 100}, {100.0, 500.0}};
    wcPt2D winMin(100, 100);
    wcPt2D winMax(300, 300), p1(100, 50), p2(200, 200), p3(200, 50), p4(350, 200);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 2.0);
    glViewport(0, 0, 1000, 1000);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(100, 300);
    glVertex2i(300, 300);
    glVertex2i(300, 100);
    glEnd();
    lineClipLiangBarsk(winMin, winMax, p1, p2);
    lineClipLiangBarsk(winMin, winMax, p3, p4);
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 300);
    glutCreateWindow("test");
    init();
    glutDisplayFunc(&displayFcn);
    glutMainLoop();
}
