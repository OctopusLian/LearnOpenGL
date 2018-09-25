#include "stdafx.h"
//三角形的绘制程序
#include <GL/glut.h>

//旋转参数
static GLfloat xRot=0.0f;
static GLfloat yRot=0.0f;

//确定多边形绕法的方向
bool bWinding = true;

//初始化窗口
void init()
{
    //设置窗口背景颜色为黑色
    glClearColor(0.0f,0.0f,0.0f,1.0f);
}

//显示函数：绘制几何体的命令
void display()
{
    //清除背景
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();  //把当前变换矩阵压入堆栈

    glRotatef(xRot,1.0f,0.0f,0.0f);//使整个场景绕着x轴旋转
    glRotatef(yRot,0.0f,1.0f,0.0f);//使整个场景绕着y轴旋转

    //设置点的大小和线宽
    glPointSize(5);
    glLineWidth(5);

    //设置多边形绕法的方向是顺时针还是逆时针
    if (bWinding)
    {
        glFrontFace(GL_CW);   //CW---clock wise顺时针
    }
    else
    {
        glFrontFace(GL_CCW);  //CCW---
    }

    //绘制三角形
    glBegin(GL_TRIANGLES);
        glColor3f(0.8f,1.0f,0.0f);
        glVertex3f(0,30,30);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(-40,-40,40);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(40,-40,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(60,-20,0);

        glColor3f(0.0f,0.7f,1.0f);
        glVertex3f(30,-60,0);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(-100.3, 10.2, 10.5);
        glVertex3f(60, -10.2, -11);
    glEnd();

    glPopMatrix();  //还原

    glutSwapBuffers();//刷新命令缓冲区
}

void reshape(int w,int h)
{
    if (h == 0)
    {
        h = 1;
    }
    glViewport(0,0,w,h);
    
    glMatrixMode(GL_PROJECTION);  //矩阵模式：投影视图
    glLoadIdentity();
    if (w <= h)
{
    //正交参数设置：x=[-100, 100], y=[-100.0*h/w, 100.0*h/w], z=[-100,100]
        glOrtho(-100.0f,100.0f,-100.0f*h/w,100.0f*h/w,-100.0f,100.0f);
    }
    else
    {
        glOrtho(-100.0f*w/h,100.0f*w/h,-100.0f,100.0f,-100.0f,100.0f);
    }

    glMatrixMode(GL_MODELVIEW);  //矩阵模式：模型视图
    glLoadIdentity();
}

//由键盘控制旋转
void SpecialKeys(int key,int x,int y)
{
    if (key == GLUT_KEY_UP) 
        xRot -=5.0f;
    if (key == GLUT_KEY_DOWN) 
        xRot +=5.0f;
    if (key == GLUT_KEY_LEFT) 
        yRot -=5.0f;
    if (key == GLUT_KEY_RIGHT) 
        yRot +=5.0f;
    
    if (xRot > 356.0f) 
        xRot = 0.0f; 
    if (xRot < -1.0f) 
        xRot = 355.0f; 
    if (yRot > 356.0f) 
        yRot = 0.0f; 
    if (yRot < -1.0f) 
        yRot = 355.0f;
    glutPostRedisplay();//刷新窗口
}

//菜单处理
void ProcessMenu(int value)
{
    switch(value)
    {
    case 1:
        {
            //修改多边形正面为填充模式
            glPolygonMode(GL_FRONT,GL_FILL);
            break;
        }
    case 2:
        {
            //修改多边形正面为线模式
            glPolygonMode(GL_FRONT,GL_LINE);
            break;
        }
    case 3:
        {
            //修改多边形正面为点填充模式
            glPolygonMode(GL_FRONT,GL_POINT);
            break;
        }
    case 4:
        {
            //修改多边形背面为填充模式
            glPolygonMode(GL_BACK,GL_FILL);
            break;
        }
    case 5:
        {
            //修改多边形背面为线模式
            glPolygonMode(GL_BACK,GL_LINE);
            break;
        }
    case 6:
        {
            //修改多边形背面为点填充模式
            glPolygonMode(GL_BACK,GL_POINT);
            break;
        }
    case 7:
        {
            //设置多边形的阴影模式为平面明暗模式
            glShadeModel(GL_FLAT);
            break;
        }
    case 8:
        {
            //设置多边形的阴影模式为光滑明暗模式
            glShadeModel(GL_SMOOTH);
            break;
        }
    case 9:
        {
            bWinding = !bWinding;
            break;
        } 
    default:
        break;
    }
    //提交修改并强制重新绘图
    glutPostRedisplay();
}

void main()
{    
    init();    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);  //双缓冲
    glutCreateWindow("多边形演示");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);//设置特殊键响应回调函数

    //菜单的句柄
    int nModeMenu;
    int nMainMenu;
    int nColorMenu;

    //创建一个子菜单并定于菜单回调函数
    nModeMenu = glutCreateMenu(ProcessMenu);
    //添加菜单项，1表示选择菜单条目时传递的参数值
    glutAddMenuEntry("正面多边形填充模式",1);
    glutAddMenuEntry("正面线框模式",2);
    glutAddMenuEntry("正面点模式",3);
    glutAddMenuEntry("反面多边形填充模式",4);
    glutAddMenuEntry("反面线框模式",5);
    glutAddMenuEntry("反面点模式",6);
    
    //添加一个子菜单
    nColorMenu = glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("平面明暗模式",7);
    glutAddMenuEntry("光滑明暗模式",8);

    //创建主菜单
    nMainMenu = glutCreateMenu(ProcessMenu);
    glutAddSubMenu("多边形模式",nModeMenu);
    glutAddSubMenu("颜色模式",nColorMenu);
    glutAddMenuEntry("改变绕法",9);
 
    //将创建的菜单与右键关联，即把菜单设置为右键弹出式菜单
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
}