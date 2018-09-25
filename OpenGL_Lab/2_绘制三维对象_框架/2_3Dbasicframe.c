// opengltest2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926
//金字塔初始旋转角度
GLfloat rtri = 0;
//用户自定义三维空间的齐次坐标矩阵(4X4)——用于输出查看变化矩阵的变化
typedef float Mat44[16];
//自定义初始化opengl 环境
void init(void)
{
    //设置背景色——用于填充背景
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //设置多边形填充模式为smooth 方式
    glShadeModel(GL_SMOOTH);
    //打开深度测试开关——用于检测物体间的z 深度差异
    glEnable(GL_DEPTH_TEST);
    //线的抗锯齿开关
    glEnable(GL_LINE_SMOOTH);
    //启用抗锯齿效果
    glHint(GL_LINE_SMOOTH,GL_NICEST);
    //指定混合函数
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //启用色彩混合状态
    glEnable(GL_BLEND);
}
//输出4X4 矩阵的结果
void outputmat(const Mat44 &mat) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++)
            printf("%.3f ", mat[i * 4 + j]);
        printf("\n");
    }
}

//自定义绘制圆函数
void glCircle()
{
    double n=50;//分段数
    float R=1.0;//半径
    int i;
    //将绘图前的模型变换矩阵压入堆栈
    glPushMatrix();
    //设置颜色RGB 与透明度值(0.5)
    glColor4f(0.0,0.2,0.8, 0.5);
    //发出准备绘图命令
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0,0.0);
    for(i=0; i<=n; i++)
        glVertex2f(R*cos(2*PI/n*i), R*sin(2*PI/n*i));
    //发出结束绘图命令
    glEnd();
    //绘图后，恢复绘图前的模型变换矩阵
    //这样，对当前图形的变换对后面图形绘制不影响
    glPopMatrix();
}

//opengl 用户自定义绘图函数
void display(void)
{
    //清除颜色缓存和深度缓存
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //装入单位转换矩阵[1 0 0 0; 0 1 0 0; 0 0 1 0; 0 0 0 1]
    glLoadIdentity();
    //平移变换命令——之后绘制的所有对象将沿Z 轴向屏幕内移动5 个单位
    glTranslatef(0.0f,0.0f,-5.0f);
    //旋转变换命令——后绘制的所有对象将沿Y 轴正向旋转rtri 个角度单位
    glRotatef(rtri,0.0f,1.0f,0.0f);
    //以下绘制的对象沿X 轴转动10 度
    //glRotatef(10, 1, 0, 0);
    //查看当前的4X4 矩阵变量
    Mat44 mat;
    //取得模型-视图变换矩阵
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    //在DOS 控制台查看上述变换后的总变换矩阵结果
    outputmat(mat);
    //设置点元大小为5 个像素
    glPointSize(5);
    //发出命令：开始绘制点
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);//点的颜色为红色
    glVertex3f(0.7, 0.5, 0.4);//顶点（vertex）位置：(0.7, 0.5, 0.4)
    glColor3f(1, 0, 0);
    glVertex3f(0.7, 0.5, -0.4);
    glEnd();//结束绘制点
    //绘制坐标轴--X，Y，Z
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(3, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0,0,0);
    glVertex3f(0,3,0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 3);
    glEnd();
    //绘制2 个三角形
    glBegin(GL_TRIANGLES);
    glColor4f(0, 0, 1, 0.5);
    glVertex2f(-0.7, 0);
    glVertex2f(0.5, 0);
    glVertex2f(0, 0.5);
    glColor4f(0, 1, 1, 0.5);
    glVertex3f(-0.5, -0.2, 0);
    glVertex3f(0.8, -0.2, 0.3);
    glVertex3f(0, 0.2, -0.5);
    glEnd();
    //绘制实心的圆环——在原有变换基础上，又增加了新的变换；
    //为了不影响后续对象的变换，采用压栈的方式，保存当前变换矩阵
    glPushMatrix();
    {
        glTranslatef(0.0f, 0.0f, -3.0f);//用于实心圆环的变换
        glColor4f(1.0f, 0.0f, 0.0f, 0.5);
        glutSolidTorus(0.3, 0.7, 30.0f, 30.0f);//绘制实心圆环
    }
    glPopMatrix(); //从堆栈中恢复已压栈的变换矩阵
    //绘制实心球
    glPushMatrix();
    {
        glTranslatef(1.0f, 1.0f, 3.0f);//增加了变换
        glColor4f(0.0f, 1.0f, 0.0f, 0.5);
        glTranslatef(0.5, 0, 0);
        glutSolidSphere(0.4f, 30.0f, 30.0f);//绘制球体
        glTranslatef(0, 0, -50);
        glutSolidSphere(0.4f, 30.0f, 30.0f);//绘制球体
    }
    glPopMatrix();
    //glScalef( 2.0, 2.0, 0.0 ); //比例变换
    //开始绘制直线段
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    //平移变换
    glTranslatef(-2, 0, 0);
    glCircle();
    //平移变换
    glTranslatef(2, 0, 0);
    //绘制立方体线框
    glColor4f(1, 1, 1, 0.5);
    glRotatef(30, 1, 0, 0);
    glutWireCube(1);
    rtri += 0.3;//全局的旋转变量加0.3 度      
    //用缓冲区所绘制的对象替换窗口内容——适合于双缓冲技术
    glutSwapBuffers();//交换双缓存
}

//用户自定义窗口调整大小事件的处理函数
//在这个函数中要求设置视口、投影、透视变换的相关参数
void reshape (int w, int h)
{
    //设置视口参数为整个窗口范围内
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    //设置投影参数:投影矩阵初始为单位阵
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    //设置透视参数: 眼睛或摄像机的视角参数为60 度，视景体的宽度和高度比，视距（焦距）
    //(near)和视径(far)参数
    //near = 1, far = 100, Z 轴负向顺着视线方向指向屏幕内
    //X 轴正向向右，Y 轴正向向上，坐标原点在屏幕中心处
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    //设置摄像机的位置及姿态参数:
    //摄像机位置(cX, cY, cZ)
    //视点所观察中心位置Ow(oX, oY, oZ)
    //摄像机位姿参数——摄像机顶部矢量
    gluLookAt(0, 0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //设置矩阵模式为模型-视图变换模式，以便于后面的自定义显示函数继续本模式
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//用户自定义键盘事件处理函数
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x':
        case 27: //ESC 键盘
        exit(0);
        break;
        default:
        break;
    }
}

int main(int argc, char** argv)
{
    //用命令行参数初始化OpenGL
    glutInit(&argc, argv);
    //使用RGB 色彩、双缓存和深度模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //初始化绘图窗口大小参数
    glutInitWindowSize(1024, 768);
    //窗口左上角坐标参数
    glutInitWindowPosition(0, 0);
    //创建窗口
    glutCreateWindow("OpenGL HelloWorld");
    //用户自定义初始化绘图环境函数
    init();
    //用户指定的绘图函数，display 名可变
    glutDisplayFunc(display);
    //窗口调整大小事件的处理函数
    glutReshapeFunc(reshape);
    //窗口键盘处理事件的处理函数
    glutKeyboardFunc(keyboard);
    //设置窗口空闲时调用的函数
    glutIdleFunc(display);
    //进入glut 函数库的主循环
    glutMainLoop();
    return 0;
}