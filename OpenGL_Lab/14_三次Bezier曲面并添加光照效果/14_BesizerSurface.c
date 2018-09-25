#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
/* 控制点的坐标 */
GLfloat ctrlpoints[4][4][3] = {
    { { -1.5, -1.5, 2.0 },
    { -0.5, -1.5, 2.0 },
    { 0.5, -1.5, -1.0 },
    { 1.5, -1.5, 2.0 } },

    { { -1.5, -0.5, 1.0 },
    { -0.5, 1.5, 2.0 },
    { 0.5, 0.5, 1.0 },
    { 1.5, -0.5, -1.0 } },

    { { -1.5, 0.5, 2.0 },
    { -0.5, 0.5, 1.0 },
    { 0.5, 0.5, 3.0 },
    { 1.5, -1.5, 1.5 } },

    { { -1.5, 1.5, -2.0 },
    { -0.5, 1.5, -2.0 },
    { 0.5, 0.5, 1.0 },
    { 1.5, 1.5, -1.0 } } };

void init(void)
{
    //背景色
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //将控制点坐标映射为曲面坐标
    //参数1：GL_MAP1_VERTEX_3，3维点坐标
    //参数2和3：控制参数u的取值范围[0, 1]
    //参数4：x方向元素间的步长为3个GLfloat
    //参数5：x方向曲线间的步长为4个控制点——曲线由4个控制点确定
    //参数6-7：控制参数v的取值范围[0, 1]
    //参数8：y方向元素间的步长为12个GLfloat元素
    //参数9：y方向每条曲线的控制点数量为4
    //note: 若是在这里设置了相关参数，后续对ctrlpoints内容更改曲线不变
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    //允许二维映射
    glEnable(GL_MAP2_VERTEX_3);
    //二维映射：x、y方向U和V的参数[0, 1]，且中间插值数量为各20个
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    //允许深度测试
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //代码开关4：取消下面两行代码，查看曲面显示效果差异
    //打开自动法矢量开关
    //glEnable(GL_AUTO_NORMAL);
    //允许正则化法矢量
    //glEnable(GL_NORMALIZE);

    //代码开关3：设置材质与光源
    GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
    GLfloat position[] = { 0.0, 1.0, 3.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.2, 0.4, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 80.0 };
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    //如果不希望旋转，则启用push和pop矩阵命令，并注释掉glRotatef行
    //glPushMatrix();
    //代码开关1：去掉注释查看效果；更改旋转角度参数，查看效果
    glRotatef(1.0, 1.0, 1.0, 1.0);
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    //glPopMatrix();
    glutSwapBuffers();
}

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
    glutCreateWindow("Bezier曲面");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);//设置空闲时调用的函数
    glutMainLoop();
    return 0;
}