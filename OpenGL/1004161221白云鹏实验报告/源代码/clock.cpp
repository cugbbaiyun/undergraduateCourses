#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
using namespace std;
int len = 800, wid = 800;
int r = 800;
int lowr = 780;
double shortlinesz = 70;
double longlinesz = 120;
double duisz = 10;
double hoursz = 420;
double minutesz = 600;
double secondsz = 680;
const double pi = acos(-1);
void init()
{
    // gluOrtho2D(-1000, 1000, -1000, 1000);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
}
void drawString(const char *str)
{
    static int isFirstCall = 1;
    static GLuint lists;
    if (isFirstCall)
    {
        isFirstCall = 0;
        lists = glGenLists(128);
        wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
    }
    for (; *str != '\0'; ++str)
    {
        glCallList(lists + *str);
    }
}

void getBase()
{
    double midx = len / 500;
    glLineWidth(3);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    double gap = 2 * pi / 1000;
    for (double start = 0; start < 2 * pi; start += gap)
    {
        double nowx = r * cos(start);
        double nowy = r * sin(start);
        glVertex3d(nowx, nowy, 5);
    }
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (double start = 0; start < 2 * pi; start += gap)
    {
        double nowx = lowr * cos(start);
        double nowy = lowr * sin(start);
        glVertex3d(nowx, nowy, 5);
    }
    glEnd();

    glPointSize(5);
    glColor3f(0, 0, 0);

    glBegin(GL_POINTS);
    glVertex3f(0, 0, 5);
    glEnd();
}

void getLine()
{
    double gap = 2 * pi / 60;
    int i = 0;
    glColor3f(0, 1, 0);
    for (double start = 0; start < 2 * pi; start += gap, ++i)
    {
        double startx = r * cos(start);
        double starty = r * sin(start);
        double endx = (r - shortlinesz) * cos(start);
        double endy = (r - shortlinesz) * sin(start);
        if (i % 5 == 0)
        {
            endx = (r - longlinesz) * cos(start);
            endy = (r - longlinesz) * sin(start);
        }
        glBegin(GL_LINES);
        glVertex3d(startx, starty, 5);
        glVertex3d(endx, endy, 5);
        glEnd();
    }
}

string to_string(int i)
{
    string str;
    str.clear();
    while (i != 0)
    {
        int c = i % 10;
        char t = '0' + c;
        str.push_back(t);
        i /= 10;
    }
    reverse(str.begin(), str.end());
    return str;
}

void getPointer()
{
    time_t tt;
    tt = time(NULL);
    tm *t = localtime(&tt);
    int hr = t->tm_hour;
    double second = t->tm_sec;
    double minute = t->tm_min;
    hr = hr % 12;
    double hour = hr;
    double hourangle = pi / 2 - (2 * pi * hour / 12 + pi / 6 * (minute / 60));
    double minuteangle = pi / 2 - (minute * 2 * pi / 60 + 2 * pi / 60 * (second / 60));
    double secondangle = pi / 2 - (second * 2 * pi / 60);
    glLineWidth(3.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 5);
    glVertex3f(hoursz * cos(hourangle), hoursz * sin(hourangle), 5);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0, 0, 5);
    glVertex3f(minutesz * cos(minuteangle), hoursz * sin(minuteangle), 5);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0, 0, 5);
    glVertex3f(secondsz * cos(secondangle), secondsz * sin(secondangle), 5);
    glEnd();
    glRasterPos2i(-80, -880);
    char str[128];
    string str1 = to_string(t->tm_hour);
    string str2 = to_string(t->tm_min);
    string str3 = to_string(t->tm_sec);
    int i = 0;
    if (str1.size() < 2)
    {
        str[i++] = '0';
    }
    for (auto c : str1)
    {
        str[i++] = c;
    }
    str[i++] = ':';
    if (str2.size() < 2)
    {
        str[i++] = '0';
    }
    for (auto c : str2)
    {
        str[i++] = c;
    }
    str[i++] = ':';
    if (str3.size() < 2)
    {
        str[i++] = '0';
    }
    for (auto c : str3)
    {
        str[i++] = c;
    }
    str[i] = '\0';
    drawString(str);
}

void display()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    getBase();
    getLine();
    getPointer();
    glFlush();
}

void timer(int id)
{
    glutPostRedisplay();
    glutTimerFunc(10, &timer, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(len, wid);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Clock");
    init();
    glutDisplayFunc(&display);
    glutTimerFunc(10, &timer, 1);
    glutMainLoop();
    return 0;
}
