// opengltest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/glut.h>
const GLfloat d = 0.04;
//主函数每次显示调用的用户自定义显示函数
void myDisplay(void)
{
    //清除色彩位缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = -25; i < 25; i++)
    {
        for (int j = -25; j < 25; j++)
        {
            if (j%2==0)
            {
                if (i%2==0)
                {
                    //glRectf 按浮点坐标与矩形宽度和高度参数绘制矩形
                    glRectf(j*d , d *i, (j + 1)*d , d *(i + 1));
                }
            }
            else
            {
                if ((i+200)%2==1)
                {
                    glRectf(j*d , d *i, (j + 1)*d , d *(i + 1));
                }
            }
        }
    }
    //按上述命令绘制图形，glFlush命令只适用于单缓冲模式
    glFlush();
}

int main(int argc, char *argv[])
{
    //初始化opengl工具箱函数库
    glutInit(&argc,argv);
    //设置RGB色彩模式与单缓冲绘图模式
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    //设置图像显示窗口的左上角位置(0,0)
    glutInitWindowPosition(0,0);
    //设置窗口大小(600,600)
    glutInitWindowSize(600,600);
    //设置窗口标题
    glutCreateWindow("Open GL 程序 Step 1");
    //设置主程序循环显示过程中所调用的显示函数
    //&myDisplay，表示取得函数名所对应的地址（函数地址）
    glutDisplayFunc(&myDisplay);
    //程序主循环
    glutMainLoop();
    return 0;
}