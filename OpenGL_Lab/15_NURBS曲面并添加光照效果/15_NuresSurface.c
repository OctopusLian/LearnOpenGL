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

GLUnurbsObj *theNurb; // 指向一个NURBS曲面对象的指针

void init(void)
{
    //背景色
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //代码开关3：设置材质与光源
    GLfloat ambient[] = { 0.4, 0.6, 0.2, 1.0 };
    GLfloat position[] = { 1.0, 1.0, 3.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.6, 0.3, 1.0 };
    GLfloat mat_specular[] = { 0.8, 0.6, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 45.0 };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //允许深度测试
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    //代码开关4：取消下面两行代码，查看曲面显示效果差异
    //打开自动法矢量开关
    glEnable(GL_AUTO_NORMAL);
    //允许正则化法矢量
    glEnable(GL_NORMALIZE);
    theNurb = gluNewNurbsRenderer(); // 创建一个NURBS曲面对象  
    //修改NURBS曲面对象的属性——glu库函数
    ////采样sampling容错torerance
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 5.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    //各控制点影响力参数设置
    GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0,
        1.0, 1.0, 1.0, 1.0 }; // NURBS曲面的控制向量      
    glRotatef(1.0, 0.7, -0.6, 1.0); // 旋转变换  
    gluBeginSurface(theNurb); // 开始曲面绘制 
    //网络查询：参数GL_MAP2_VERTEX_3的作用？
    //将
    gluNurbsSurface(theNurb, 8, knots, 8, knots, 4 * 3, 3, &ctrlpoints[0][0][0], 4, 4, GL_MAP2_VERTEX_3); // 定义曲面的数学模型，确定其形状  
    gluEndSurface(theNurb); // 结束曲面绘制  
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