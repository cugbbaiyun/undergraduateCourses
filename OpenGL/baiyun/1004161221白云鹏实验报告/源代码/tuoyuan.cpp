#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
using namespace std;
//初始化Opengl的设置
void init()
{
    //设置背景颜色为白色
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    //设置投影面
    gluOrtho2D(0.0, 1000, 0.0, 1000);
    glViewport(0, 0, 1000, 10000);
}
//设置像素的颜色
void setPixiel(int x, int y)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
//四分法绘制椭圆
void duichen(int x0, int y0, int x, int y)
{
    setPixiel(x0 + x, y0 + y);
    setPixiel(x0 + x, y0 - y);
    setPixiel(x0 - x, y0 + y);
    setPixiel(x0 - x, y0 - y);
}
//绘制椭圆
void drawEllipse(int x0, int y0, int a, int b)
{
    double aa = a * a;
    double bb = b * b;
    double d = bb + aa * (0.25 - b);
    int x = 0, y = b;
    duichen(x0, y0, x, y);
    //椭圆的上半部分
    while (bb * (x + 1) < aa * (y - 0.5))
    {
        if (d < 0)
        {
            d += bb * (2 * x + 3);
        }
        else
        {
            d += (bb * (2 * x + 3) + aa * ((-2) * y + 2));
            --y;
        }
        ++x;
        duichen(x0, y0, x, y);
    }
    d = (b * (x + 0.5)) * 2 + (a * (y - 1)) * 2 - (a * b) * 2;
    //椭圆的下半部分
    while (y > 0)
    {
        if (d < 0)
        {
            d += bb * (2 * x + 2) + aa * ((-2) * y + 3);
            ++x;
        }
        else
        {
            d += aa * ((-2) * y + 3);
        }
        --y;
        duichen(x0,y0,x,y);
    }
}
//回调函数
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    int x0 = 120,y0=100,a=100,b=60;
    drawEllipse(x0,y0,a,b);
    glFlush();
}
int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(900,900);
    glutCreateWindow("Ellipse");
    glutDisplayFunc(&display);
    init();
    glutMainLoop();
}