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
void drawLine(GLint x0, GLint y0, GLint x1, GLint y1)
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(x0, y0);
    glVertex2i(x1, y1);
    glEnd();
}
const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

inline GLint round(const GLfloat a) { return GLint(a + 0.5); }
inline GLint inside(GLint code) { return GLint(!code); }
inline GLint reject(GLint code1, GLint code2) { return GLint(code1 & code2); }
inline GLint accept(GLint code1, GLint code2)
{
    return GLint(!(code1 | code2));
}

GLubyte encode(wcPt2D pt, wcPt2D winMin, wcPt2D winMax)
{
    GLubyte code = 0x00;
    if (pt.getx() < winMin.getx())
    {
        code = code | winLeftBitCode;
    }
    if (pt.getx() > winMax.getx())
    {
        code = code | winRightBitCode;
    }
    if (pt.gety() < winMin.gety())
    {
        code = code | winBottomBitCode;
    }
    if (pt.gety() > winMax.gety())
    {
        code = code | winTopBitCode;
    }
    return code;
}

void swapPts(wcPt2D *p1, wcPt2D *p2)
{
    wcPt2D tem;
    tem = *p1;
    *p1 = *p2;
    *p2 = tem;
}

void swapCodes(GLubyte *c1, GLubyte *c2)
{
    GLubyte tem;
    tem = *c1;
    *c1 = *c2;
    *c2 = tem;
}

void lineClipCohSuth(wcPt2D winMin, wcPt2D winMax, wcPt2D p1, wcPt2D p2)
{
    GLubyte code1, code2;
    GLint done = false, plotLine = false;
    GLfloat m;
    while (!done)
    {
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);
        if (accept(code1, code2))
        {
            done = true;
            plotLine = true;
        }
        else if (reject(code1, code2))
            done = true;
        else
        {
            if (inside(code1))
            {
                swapPts(&p1, &p2);
                swapCodes(&code1, &code2);
            }
            if (p2.getx() != p1.getx())
            {
                m = (p2.gety() - p1.gety()) / (p2.getx() - p1.getx());
            }
            if (code1 & winLeftBitCode)
            {
                p1.y += (winMin.getx() - p1.x) * m;
                p1.x = winMax.x;
            }
            else if (code1 & winRightBitCode)
            {
                p1.y += (winMax.x - p1.x) * m;
                p1.x = winMax.x;
            }
            else if (code1 & winBottomBitCode)
            {
                if (p2.x != p1.x)
                    p1.x += (winMin.y - p1.y) / m;
                p1.y = winMin.y;
            }
            else if (code1 & winTopBitCode)
            {
                if (p2.x != p1.x)
                    p1.x += (winMax.y - p1.y) / m;
                p1.y = winMax.y;
            }
        }
    }
    if(plotLine){
        drawLine(round(p1.x),round(p1.y),round(p2.x),round(p2.y));
    }
}



void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
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
    lineClipCohSuth(winMin,winMax,p1,p2);
    lineClipCohSuth(winMin,winMax,p3,p4);
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
