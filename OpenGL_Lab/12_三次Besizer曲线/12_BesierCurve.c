#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

//4个控制点的3D坐标——z坐标全为0
GLfloat ctrlpoints[4][3] = {
    { -4, -4, 0 }, { -2, 4, 0 }, { 2, -4, 0 }, { 4, 4, 0 }
};

void init(void)
{
    //背景色
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //将控制点坐标映射为曲线坐标
    //参数1：GL_MAP1_VERTEX_3，3维点坐标
    //参数2和3：控制参数t或u的取值范围[0, 1]
    //参数4：曲线内插值点间的步长3————3维坐标
    //参数5：曲线间的补偿为顶点数4个————总步长为12
    //参数6：控制点二维数组首元素地址
    //注意: 若是在这里设置了相关参数，后续对ctrlpoints内容更改曲线不变
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    //打开开关——允许3维坐标控制点到参数点转换开关
    glEnable(GL_MAP1_VERTEX_3);
    glShadeModel(GL_FLAT);

    //代码开关2：去掉本注释，可启用反走样
    /*
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);  //允许直线反走样
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
}

void display(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //代码开关1：去掉本注释，查看动态的曲线绘图效果：动态更新控制点坐标
    /*
    for(int t = 0; t < 4; t++) {
    for(int j = 0; j < 3; j++)
    ctrlpoints[t][j] = (rand() % 1024 / 1024.0 - 0.5) * 10;
    }
    //动态映射
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    */
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);
    //绘制连续线段
    glBegin(GL_LINE_STRIP);
    //参数t或u取值为i/30，共计31个点
    for (i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0);   //根据4个控制点坐标的参数化插值
    glEnd();
    /* 显示控制点 */
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();

    glTranslatef(-0.1f, 0.1f, 0.0f);
    glColor3f(0.0, 1.0, 0.0);
    //glLineWidth(2.0);
    //绘制连续线段——线段数越多，曲线越光滑
    glBegin(GL_LINE_STRIP);
    //设置参数t或u取值为i/60，共计61个点
    //实验：若让t从-2变化到+2，可看到什么效果
    for (i = 0; i <= 60; i++)
        glEvalCoord1f((GLfloat)i / 60.0);  //根据4个控制点坐标的参数化插值
    glEnd();

    glTranslatef(-0.1f, 0.1f, 0.0f);
    glColor3f(1.0, 1.0, 1.0);
    //绘制连续线段
    glBegin(GL_LINE_STRIP);
    //设置参数t或u取值为i/60，共计61个点
    //实验：若让t从-2变化到+2，可看到什么效果
    for (i = 0; i <= 100; i++)
        glEvalCoord1f((GLfloat)i / 100.0);
    glEnd();

    glutSwapBuffers();
}

//3D空间中绘制2D效果，采用正交投影
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0*(GLfloat)h / (GLfloat)w, 5.0*(GLfloat)h / (GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-5.0*(GLfloat)w / (GLfloat)h, 5.0*(GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
    case 'X':
    case 27:   //ESC键
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//使用双缓存模式和深度缓存
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("2D Bezier曲线");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);//设置空闲时调用的函数
    glutMainLoop();
    return 0;
}