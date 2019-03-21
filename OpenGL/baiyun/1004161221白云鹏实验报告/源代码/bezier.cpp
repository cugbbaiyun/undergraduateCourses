#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = -50, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;
class wcPt3D
{
  public:
    GLfloat x, y, z;
};
void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bez)
{
    glBegin(GL_POINTS);
    glVertex2f(bez.x, bez.y);
    glEnd();
}
void binomialCoeffs(GLint n, GLint *c)
{
    GLint k, j;
    for (k = 0; k <= n; ++k)
    {
        c[k] = 1;
        for (j = n; j >= k + 1; --j)
        {
            c[k] *= j;
        }
        for (j = n - k; j >= 2; --j)
        {
            c[k] /= j;
        }
    }
}
void computeBzePt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *c)
{
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;
    bezPt->z = bezPt->y = bezPt->x = 0.0;
    for (k = 0; k < nCtrlPts; ++k)
    {
        bezBlendFcn = c[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}
void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurverPts)
{
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *c, k;
    c = new GLint(nCtrlPts);
    binomialCoeffs(nCtrlPts - 1, c);
    for (k = 0; k <= nBezCurverPts; ++k)
    {
        u = GLfloat(k) / GLfloat(nBezCurverPts);
        computeBzePt(u, &bezCurvePt, nCtrlPts, ctrlPts, c);
        plotPoint(bezCurvePt);
    }
    delete[] c;
}
void displayFcn()
{
    GLint nCtrlPts = 4, nBezCurvePts = 1000;
    wcPt3D ctrlPts[4] = {{-40.0, -40.0, 0.0}, {-10.0, 200.0, 0.0}, {10.0, -200.0, 0.0}, {40.0, 40.0, 0.0}};
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    glColor3f(1.0, 0.0, 0.0);
    bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    glFlush();
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newHeight, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
    glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Bezier");
    init();
    glutDisplayFunc(&displayFcn);
    glutReshapeFunc(&winReshapeFcn);
    glutMainLoop();
}