#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>   //srand和rand
#include <time.h>   //time(int)

const int N = 2000;
float particles[N][3];
float rtri = 0;

// 初始化材质属性、光源、光照模型、深度缓冲区
void init(void)
{
    //材质反光性设置
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
    GLfloat mat_shininess[] = { 50.0 };               //高光指数
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };   //灯位置(1,1,1), 最后1-开关
    GLfloat Light_Model_Ambient[] = { 1.0, 0.2, 0.5, 0.1 }; //环境光参数

    glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
    glShadeModel(GL_SMOOTH);           //多变性填充模式

    //材质属性
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数

    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
}

void display(void)
{
    //通过循环更新每个粒子的位置
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            particles[i][j] += (rand() % 800 / 800.0 - 0.5) / 100;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);            //清除颜色缓存和深度缓存

    glLoadIdentity();   //装入单位转换矩阵

    //平移
    glTranslatef(0.0f, 0.0f, -4.0f);//总体旋转
    glRotatef(rtri, 0.1, 1.0, 0.1);
    //每个粒子的位置变动
    for (int i = 0; i < N; i++) {
        glPushMatrix();
        //平移到第i个粒子位置
        glTranslatef(particles[i][0], particles[i][1], particles[i][2]);
        glutSolidSphere(0.02, 20, 16);
        glPopMatrix();
    }

    rtri += 0.5f;//加一个角度
    glutSwapBuffers();//交换双缓存
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    //投影模式
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //设置斜投影矩阵参数
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 600.0f);

    //模型-视图矩阵模式
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
    //seed初始化随机数函数
    srand((unsigned int)time(0));    //random seeds
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            particles[i][j] = (rand() % 800 / 800.0 - 0.5) * 2;
        }
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//使用双缓存模式和深度缓存
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("粒子群");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);//设置空闲时调用的函数
    glutMainLoop();
    return 0;
}