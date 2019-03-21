#include <windows.h>
#include <bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

const int pointnum = 6;
const int segmentnum = pointnum - 3;

struct point2D
{
    int x, y;
    point2D() = default;
    point2D(int xx, int yy) : x(xx), y(yy) {}
    void setPP(int xx, int yy)
    {
        x = xx;
        y = yy;
    }
};
point2D vec[pointnum];

void bline(int n)
{
    float f1, f2, f3, f4;
    float dt = 1.0 / n;
    float t;
    glBegin(GL_LINE_STRIP);
    for (int num = 0; num < segmentnum; ++num)
    {
        for (int i = 0; i <= n; ++i)
        {
            t = i * dt;
            f1 = (3 * t * t - t * t * t - 3 * t + 1) / 6.0;
            f2 = (3 * t * t * t - 6 * t * t + 4) / 6.0;
            f3 = (-3 * t * t * t + 3 * t * t + 3 * t + 1) / 6.0;
            f4 = t * t * t / 6.0;
            glVertex2f(f1 * vec[num].x + f2 * vec[num + 1].x + f3 * vec[num + 2].x + f4 * vec[num + 3].x, f1 * vec[num].y + f2 * vec[num + 1].y + f3 * vec[num + 2].y + f4 * vec[num + 3].y);
        }
    }
    glEnd();
}

void display()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    bline(20);
    glFlush();
}
void init()
{
    vec[0].setPP(200, 400);
    vec[1].setPP(100, 300);
    vec[2].setPP(200, 200);
    vec[4].setPP(250, 300);
    vec[4].setPP(400, 200);
    vec[5].setPP(400, 400);
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 900, 900);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bline");
    init();
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}