#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;
int xrota = 0, yrota = 0;
bool light0on = 1;
#define GL_BGR 0x80E0
#define BMP_Header_Length 54
float eyex, eyey, eyez;
int posx = 0,posz= 0;
GLuint ground;
int power_of_two(int n)
{
  if (n <= 0)
    return 0;
  return (n & (n - 1)) == 0;
}

struct car
{
  float scale = 1.0f;
  void drawcar()
  {
    glPushMatrix();
    glScaled(scale,scale,scale);
    glTranslated(0,0,200);
    //车下半部
    glTranslated(posx, 30, posz);
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1.0);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-40.0f, -30.0f, -50.0f);
    glVertex3f(40.0f, -30.0f, -50.0f);
    glColor3f(255.0 / 256, 185.0 / 256, 15.0 / 256);
    glColor3f(0.2, 0.5, 0.8);
    glVertex3f(40.0f, -45.0f, -50.0f);
    glVertex3f(-40.0f, -45.0f, -50.0f);
    glEnd();
    glBegin(GL_POLYGON);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glNormal3f(1.0, 0, 0);
    glVertex3f(40.0f, -30.0f, -80.0f);
    glVertex3f(40.0f, -30.0f, -50.0f);
    glColor3f(30.0 / 256, 144.0 / 256, 255.0 / 256);
    glVertex3f(40.0f, -45.0f, -50.0f);
    glVertex3f(40.0f, -45.0f, -80.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(-1.0, 0, 0);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-40.0f, -30.0f, -80.0f);
    glVertex3f(-40.0f, -30.0f, -50.0f);
    //    glColor3f(30.0 / 256, 144.0 / 256, 255.0 / 256);
    glVertex3f(-40.0f, -45.0f, -50.0f);
    glVertex3f(-40.0f, -45.0f, -80.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1);
    //    glColor3f(0.1, 0.2, 0.8);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-40.0f, -30.0f, -80.0f);
    glVertex3f(40.0f, -30.0f, -80.0f);
    //    glColor3f(1, 0.5, 0.8);
    glColor3f(30.0 / 256, 144.0 / 256, 255.0 / 256);
    glVertex3f(40.0f, -45.0f, -80.0f);
    glVertex3f(-40.0f, -45.0f, -80.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0, 1.0, 0);
    //    glColor3f(0.5, 0, 1);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-40.0f, -30.0f, -50.0f);
    glVertex3f(-40.0f, -30.0f, -80.0f);
    glVertex3f(40.0f, -30.0f, -80.0f);
    glVertex3f(40.0f, -30.0f, -50.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0, 1.0, 0);
    //    glColor3f(0.8, 0.5, 0.2);
    //    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glColor3f(30.0 / 256, 144.0 / 256, 255.0 / 256);
    glVertex3f(-40.0f, -45.0f, -50.0f);
    glVertex3f(-40.0f, -45.0f, -80.0f);
    glVertex3f(40.0f, -45.0f, -80.0f);
    glVertex3f(40.0f, -45.0f, -50.0f);
    glEnd();
    //车上半部
    glBegin(GL_POLYGON);
    //    glColor3f(0.8, 0.5, 1);
    glNormal3f(0, 0, 1);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-20.0f, -30.0f, -50.0f);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-10.0f, -20.0f, -50.0f);
    glVertex3f(20.0f, -20.0f, -50.0f);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(25.0f, -30.0f, -50.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, 1.0);
    //    glColor3f(0.5, 0.8, 1);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-20.0f, -30.0f, -80.0f);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-10.0f, -20.0f, -80.0f);
    glVertex3f(20.0f, -20.0f, -80.0f);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(25.0f, -30.0f, -80.0f);
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0, 1, 0);
    //    glColor3f(0.4, 0.2, 1);
    //    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-10.0f, -20.0f, -50.0f);
    glVertex3f(-10.0f, -20.0f, -80.0f);
    glVertex3f(20.0f, -20.0f, -80.0f);
    glVertex3f(20.0f, -20.0f, -50.0f);
    glEnd();
    glBegin(GL_POLYGON);
    //    glColor3f(0.5, 0.8, 0);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-10.0f, -20.0f, -50.0f);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(-20.0f, -30.0f, -50.0f);
    glVertex3f(-20.0f, -30.0f, -80.0f);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glVertex3f(-10.0f, -20.0f, -80.0f);
    glEnd();
    glBegin(GL_POLYGON);
    //    glColor3f(0.9, 0.5, 0.5);
    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);

    glVertex3f(20.0f, -20.0f, -50.0f);
    glVertex3f(20.0f, -20.0f, -80.0f);
    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    glVertex3f(25.0f, -30.0f, -80.0f);
    glVertex3f(25.0f, -30.0f, -50.0f);
    glEnd();
    glBegin(GL_POLYGON);
    //    glColor3f(0.3, 0.8, 1);
    //    glColor3f(254.0 / 256, 67.0 / 256, 101.0 / 256);
    //    glColor3f(252.0 / 256, 157.0 / 256, 154.0 / 256);
    glNormal3f(0, 1, 0);
    glVertex3f(-30.0f, -45.0f, -50.0f);
    glVertex3f(-30.0f, -45.0f, -80.0f);
    glVertex3f(30.0f, -45.0f, -80.0f);
    glVertex3f(30.0f, -45.0f, -50.0f);
    glEnd();
    //车轮
    glPushMatrix();
    glColor3f(105.0 / 256, 105.0 / 256, 105.0 / 256);
    glTranslated(-20.0f, -45.0f, -50.0f);
    glutSolidTorus(2, 5, 5, 100);
    glTranslated(0.0f, 0.0f, -30.0f);
    glutSolidTorus(2, 5, 5, 100);
    glTranslated(45.0f, 0.0f, 0.0f);
    glutSolidTorus(2, 5, 5, 100);
    glTranslated(0.0f, 0.0f, 30.0f);
    glutSolidTorus(2, 5, 5, 100);
    glPopMatrix();
    glPopMatrix();
  }
};
car carr;
GLuint load_texture(const char *file_name)
{
  GLint width, height, total_bytes;
  GLubyte *pixels = 0;
  GLuint last_texture_ID = 0, texture_ID = 0;

  // 打开文件，如果失败，返回
  FILE *pFile = fopen(file_name, "rb");
  if (pFile == 0)
  {
    cout << "12321" << endl;
    return 0;
  }

  // 读取文件中图象的宽度和高度
  fseek(pFile, 0x0012, SEEK_SET);
  fread(&width, 4, 1, pFile);
  fread(&height, 4, 1, pFile);
  fseek(pFile, BMP_Header_Length, SEEK_SET);

  // 计算每行像素所占字节数，并根据此数据计算总像素字节数
  {
    GLint line_bytes = width * 3;
    while (line_bytes % 4 != 0)
      ++line_bytes;
    total_bytes = line_bytes * height;
  }

  // 根据总像素字节数分配内存
  pixels = (GLubyte *)malloc(total_bytes);
  if (pixels == 0)
  {
    fclose(pFile);
    return 0;
  }

  // 读取像素数据
  if (fread(pixels, total_bytes, 1, pFile) <= 0)
  {
    free(pixels);
    fclose(pFile);
    return 0;
  }

  // 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
  // 若图像宽高超过了OpenGL规定的最大值，也缩放
  {
    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    if (!power_of_two(width) || !power_of_two(height) || width > max ||
        height > max)
    {
      const GLint new_width = 256;
      const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
      GLint new_line_bytes, new_total_bytes;
      GLubyte *new_pixels = 0;

      // 计算每行需要的字节数和总字节数
      new_line_bytes = new_width * 3;
      while (new_line_bytes % 4 != 0)
        ++new_line_bytes;
      new_total_bytes = new_line_bytes * new_height;

      // 分配内存
      new_pixels = (GLubyte *)malloc(new_total_bytes);
      if (new_pixels == 0)
      {
        free(pixels);
        fclose(pFile);
        return 0;
      }

      // 进行像素缩放
      gluScaleImage(GL_RGB, width, height, GL_UNSIGNED_BYTE, pixels, new_width,
                    new_height, GL_UNSIGNED_BYTE, new_pixels);

      // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
      free(pixels);
      pixels = new_pixels;
      width = new_width;
      height = new_height;
    }
  }

  // 分配一个新的纹理编号
  glGenTextures(1, &texture_ID);
  if (texture_ID == 0)
  {
    free(pixels);
    fclose(pFile);
    return 0;
  }

  // 绑定新的纹理，载入纹理并设置纹理参数
  // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
  GLint lastTextureID = last_texture_ID;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
  glBindTexture(GL_TEXTURE_2D, texture_ID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
               GL_UNSIGNED_BYTE, pixels);
  glBindTexture(GL_TEXTURE_2D, lastTextureID); //恢复之前的纹理绑定
  free(pixels);
  return texture_ID;
}

struct snowMan
{
  float faceto = 0;
  float x, z, y;
  float scale = 12;
  void setxz(int xx, int yy, int zz)
  {
    x = xx;
    y = yy;
    z = zz;
  }
  void draw()
  {
    glPushMatrix(); // 1
    glTranslated(x, y, z);
    glRotated(faceto, 0, -1, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    // glTranslatef(0.0f,scale,0.0f);
    // glutSolidSphere(scale,100,100);
    glTranslatef(0.0f, 0.75f * scale, 0.0f);
    glutSolidSphere(0.75f * scale, 100, 100);
    glPushMatrix(); // 2
    glScaled(1.5, 1.5, 1.5);
    glTranslatef(0.0f, 2.0 / 3 * scale, 0.0f);
    glutSolidSphere(0.25f * scale, 100, 100);
    glPushMatrix(); // 3
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f * scale, 0.10f * scale, 0.18f * scale);
    glutSolidSphere(0.05f * scale, 50, 50);
    glTranslatef(-0.1f * scale, 0.0f, 0.0f);
    glutSolidSphere(0.05f * scale, 50, 50);
    glPopMatrix(); // 1
    glColor3f(1.0f, 0.5f, 0.5f);
    glRotatef(0.0f, 1.0f * scale, 0.0f, 0.0f);
    glutSolidCone(0.08f * scale, 0.5f * scale, 40, 20);
    glPopMatrix(); // 2
    glPopMatrix(); // 3

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(x, y, z);
    glRotated(faceto, 0, -1, 0);
    glTranslated(-0.5f * scale, 1.2 * scale, 0);
    glutSolidSphere(0.25 * scale, 100, 100);
    glTranslated(scale, 0, 0);
    glutSolidSphere(0.25 * scale, 100, 100);
    glTranslated(0.3f * scale, -0.2f * scale, 0);
    glutSolidSphere(0.25 * scale, 100, 100);
    glTranslated(-1.6f * scale, 0, 0);
    glutSolidSphere(0.25 * scale, 100, 100);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(x, y, z);
    glRotated(faceto, 0, -1, 0);
    glTranslated(0, 0.75f / 2 * scale, 0.75f / 3 * 2 * scale);
    glutSolidSphere(0.2f * scale, 100, 100);
    glTranslated(0, 0.75f / 2 * scale, 0.75f / 6 * scale);
    glutSolidSphere(0.2f * scale, 100, 100);
    glTranslated(0, 0.75f / 2 * scale, -0.75f / 6 * scale);
    glutSolidSphere(0.2f * scale, 100, 100);
    glPopMatrix();
  }
};

void setLight()
{

  GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0}; //镜面反射参数
  GLfloat mat_shininess[] = {100.0};             //高光指数
  GLfloat light_position[] = {1.0, 60.0, 20.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 0.0};         //灯位置(1,1,1), 最后1-开关
  GLfloat Light_Model_Ambient[] = {0.8, 0.8, 0.8, 1.0}; //环境光参数

  glClearColor(0.0, 0.0, 0.0, 0.0);               //背景色
  glShadeModel(GL_SMOOTH);                        //多变性填充模式
  GLfloat mmat_specular[] = {0.8, 0.8, 0.8, 0.2}; //镜面反射参数
  glMaterialfv(GL_FRONT, GL_SPECULAR, mmat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);               //散射光属性
  glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);              //镜面反射光
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient); //环境光参数
  glEnable(GL_LIGHTING);                                       //开关:使用光
  glEnable(GL_LIGHT0);                                         //打开0#灯
  glEnable(GL_DEPTH_TEST);                                     //打开深度测试
}
snowMan sm1;
struct myclock
{
  int hr;
  double second;
  double minute;
  double hour;
  int len = 80, wid = 80;
  int r = 80;
  int lowr = 70;
  double shortlinesz = 7;
  double longlinesz = 12;
  double duisz = 1;
  double hoursz = 42;
  double minutesz = 60;
  double secondsz = 68;
  const double pi = acos(-1);
  void getTime()
  {
    time_t tt;
    tt = time(NULL);
    tm *t = localtime(&tt);
    hr = t->tm_hour;
    second = t->tm_sec;
    minute = t->tm_min;
    hr = hr % 12;
    hour = hr;
  }
  void setScale(float b)
  {
    len = len * b;
    wid = wid * b;
    r = r * b;
    lowr = lowr * b;
    shortlinesz = shortlinesz * b;
    longlinesz = longlinesz * b;
    duisz = duisz * b;
    hoursz = hoursz * b;
    minutesz = minutesz * b;
    secondsz = secondsz * b;
  }
  void getBase()
  {
    glLineWidth(1);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    double gap = 2 * pi / 2000;
    for (double start = 0; start < 2 * pi; start += gap)
    {
      double nowx = r * cos(start);
      double nowy = r * sin(start);
      glVertex2d(nowx, nowy);
    }
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (double start = 0; start < 2 * pi; start += gap)
    {
      double nowx = lowr * cos(start);
      double nowy = lowr * sin(start);
      glVertex2d(nowx, nowy);
    }
    glEnd();

    glPointSize(5);
    glColor3f(0, 0, 0);

    glBegin(GL_POINTS);
    glVertex2f(0, 0);
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
      glLineWidth(2);
      glBegin(GL_LINES);
      glVertex2d(startx, starty);
      glVertex2d(endx, endy);
      glEnd();
    }
  }

  void getPointer()
  {
    double hourangle = pi / 2 - (2 * pi * hour / 12 + pi / 6 * (minute / 60));
    double minuteangle =
        pi / 2 - (minute * 2 * pi / 60 + 2 * pi / 60 * (second / 60));
    double secondangle = pi / 2 - (second * 2 * pi / 60);
    glLineWidth(3.0);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(hoursz * cos(hourangle), hoursz * sin(hourangle));
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(minutesz * cos(minuteangle), hoursz * sin(minuteangle));
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(secondsz * cos(secondangle), secondsz * sin(secondangle));
    glEnd();
  }

  void draw(int x, int y, int z)
  {
    getTime();
    glPushMatrix();
    glTranslated(GLfloat(x), GLfloat(y), GLfloat(z));
    getBase();
    getPointer();
    getLine();
    glPopMatrix();
  }
};
myclock c1;
struct ball
{
  float x, y, z;
  float maxy;
  float floor1;
  float r, g, b;
  float v = 0;
  float rr;
  float gg;
  float dir = 1;
  float minx, maxx;
  float minz, maxz;
  void setr(int rrx) { rr = rrx; }
  void setColor(float a, float bb, float c)
  {
    r = a;
    g = bb;
    b = c;
  }
  void setfloor(int t) { floor1 = t; }
  void setLo(float xx, float yy, float zz)
  {
    x = xx;
    maxy = yy;
    y = yy;
    z = zz;
  }
  void seta(float ag) { gg = ag; }
  void calNowlo()
  {
    if (dir == 1)
    {
      y -= v;
      v += gg;
      if (y <= floor1 + rr)
      {
        y = floor1 + rr;
        dir *= -1;
      }
    }
    else if (dir == -1)
    {
      y += v;
      v -= gg;
      if (v <= 0)
      {
        v = 0;
        dir *= -1;
      }
    }
    if (y > maxy)
    {
      y = maxy;
      v = 0;
      dir = 1;
    }
  }
  int draw()
  {
    calNowlo();
    glPushMatrix();
    glTranslated(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(rr, 100, 100);
    glPopMatrix();
  }
};
ball test1;
ball test2;
void timer(int id)
{
  posx -= 2;
  if(posx < -200){
    posx = 400;
    posz += 50;
  }
  glutPostRedisplay();
  glutTimerFunc(100, timer, 1);
}

void init()
{
  ground = load_texture("C:\\glut\\test\\grass.bmp");
  sm1.setxz(-20, -30, 20);
  setLight();
  float position[4] = {0.0f, 20.0f, 0.0f, 1.0f};
  GLfloat lmodel_ambient[] = {0.4, 0.4, 0.4, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_BLEND);
  if (light0on)
    glEnable(GL_LIGHT0);
  srand(time(NULL));
  eyex = 0;
  eyey = 0;
  eyez = 200;
  test2.seta(0.2);
  test2.setColor(0, 0, 0);
  test2.setLo(-20, 30, -20);
  test2.setr(10);
  test2.setfloor(-30);
  test1.seta(0.3);
  // test1.setColor(1, 0, 0);
  test1.setColor(205.0 / 255, 232.0 / 255, 246.0 / 255);
  test1.setLo(20, 30, -20);
  test1.setfloor(-30);
  test1.setr(5);
  c1.setScale(0.4);
  glEnable(GL_DEPTH_TEST);
}

void getRoof(int startx, int endx, int startz, int endz, int y)
{
  int gap = 10;
  for (int i = startx; i < endx; i += gap)
  {
    for (int j = startz; j < endz; j += gap)
    {
      int mxi = min(endx, i + gap);
      int mxj = min(endz, j + gap);
      glColor3f(0.2, 0.3, 0.4);
      // type = !type;
      // glNormal3f(0, -1, 0);
      glBegin(GL_QUADS);
      glVertex3f(i, y, j);
      glVertex3f(i, y, mxj);
      glVertex3f(mxi, y, mxj);
      glVertex3f(mxi, y, j);
      glEnd();
    }
    // type = !type;
  }
}

void getBack(int startx, int starty, int endx, int endy, int z)
{
  int gap = 10;
  bool type = 1;
  for (int i = startx; i < endx; i += gap)
  {
    for (int j = starty; j < endy; j += gap)
    {
      int mxi = min(i + gap, endx);
      int mxj = min(j + gap, endy);
      glNormal3f(0, 0, 1);
      if (type)
      {
        glColor3f(1.0, 1.0, 1.0);
      }
      else
      {
        glColor3f(0.2, 0.3, 0.4);
      }
      type = !type;
      glNormal3f(0, 0, 1);
      glBegin(GL_QUADS);
      glVertex3f(i, j, z);
      glVertex3f(i, mxj, z);
      glVertex3f(mxi, mxj, z);
      glVertex3f(mxi, j, z);
      glEnd();
    }
    type = !type;
  }
}

void getFloor(int startx, int endx, int startz, int endz, int y)
{
  bool type = 1;
  int gap = 10;
  for (int i = startx; i < endx; i += gap)
  {
    for (int j = startz; j < endz; j += gap)
    {
      int mxi = min(endx, i + gap);
      int mxj = min(endz, j + gap);
      glColor3f(1.0, 1.0, 1.0);
      glNormal3f(0, 1, 0);
      glBegin(GL_QUADS);
      glVertex3f(i, y, j);
      glVertex3f(i, y, mxj);
      glVertex3f(mxi, y, mxj);
      glVertex3f(mxi, y, j);
      glEnd();
    }
    // type = !type;
  }
}
void SpecialKeys(int key, int x, int y)
{
  if (key == GLUT_KEY_UP)
    xrota -= 5.0f;
  if (key == GLUT_KEY_DOWN)
    xrota += 5.0f;
  if (key == GLUT_KEY_LEFT)
    yrota -= 5.0f;
  if (key == GLUT_KEY_RIGHT)
    yrota += 5.0f;
  glutPostRedisplay(); // 刷新窗口
}
void keys(unsigned char key, int x, int y)
{
  if (key == 'w')
  {
    if (eyez >= -100 + 10)
      eyez -= 10;
  }
  if (key == 'a')
  {
    if (eyex >= -100 + 10)
      eyex -= 10;
  }
  if (key == 's')
  {
    if (eyez <= 100 - 10)
      eyez += 10;
  }
  if (key == 'd')
  {
    if (eyex <= 100 - 10)
      eyex += 10;
  }
  if (key == '0')
  {
    light0on = !light0on;
  }
  if (key == 'j')
  {
    if (sm1.z <= 100 - 10)
      sm1.z += 5;
    // sm1.faceto = 0;
  }

  if (key == 'k')
  {
    if (sm1.z >= -100 + 10)
      sm1.z -= 5;
    // sm1.faceto = 180;
  }
  if (key == 'h')
  {
    // if (sm1.x >= -100 + 10)
    //     sm1.x -= 5;
    sm1.faceto += 5;
  }
  if (key == 'l')
  {
    // if (sm1.x <= 100 - 10)
    //     sm1.x += 5;
    sm1.faceto -= 5;
  }
  glutPostRedisplay();
}
void display()
{

  if (light0on)
    glEnable(GL_LIGHT0);
  else
    glDisable(GL_LIGHT0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(eyex, eyey, eyez, 0, 0, -1000, 0, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.3f, 0.3f, 0.4f);
  glPushMatrix();
  glRotatef(xrota, 1.0, 0.0, 0.0);
  glRotatef(yrota, 0.0, 1.0, 0.0);

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, ground);
  glEnable(GL_TEXTURE_2D);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-400, -29, -100);
  glTexCoord2f(0.0f, 5.0f);
  glVertex3f(-400, -29, 500);
  glTexCoord2f(5.0f, 5.0f);
  glVertex3f(400, -29, 500);
  glTexCoord2f(5.0f, 0.0f);
  glVertex3f(400, -29, -100);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
  // test2.draw();
  carr.drawcar();
  sm1.draw();
  glPushMatrix();
  c1.draw(0, 35, -99);
  glPopMatrix();
  test1.draw();
  glPushMatrix();
  glTranslated(0, 0, -20);
  glPopMatrix();
  // getFloor(-400, 400, -100, 500, -30);
  getRoof(-400, 400, -100, 500, 70);
  getBack(-400, -30, 400, 70, -100);
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glClearColor(0, 0, 0, 0);
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, GLfloat(w) / GLfloat(h), 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 800);
  glutCreateWindow("test");
  init();
  glDepthFunc(GL_LEQUAL);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(SpecialKeys);
  glutKeyboardFunc(keys);
  glutTimerFunc(1000, timer, 1);
  glutMainLoop();
  return 0;
}
