#include "stdafx.h"
#include<Windows.h>
#include<GL\glut.h>
#include<GL\GLAUX.H>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")

GLfloat  xrot = 0;   // X 旋转量
GLfloat  yrot = 0;   // Y 旋转量
GLfloat  zrot = 0;   // Z 旋转量
GLuint  texture[1];  // 存储一个纹理---数组

const GLfloat Pi = 3.1415926536;
const GLfloat R = 0.8f;
const int n = 200;
static GLfloat angle = 2 * Pi;

//载入位图图象到内存
AUX_RGBImageRec *LoadBMP(CHAR *Filename)
{
    FILE *File = NULL;         // 文件句柄
    if (!Filename)          // 确保文件名已提供
    {
        return NULL;         // 如果没提供，返回 NULL
    }
    File = fopen(Filename, "r");       // 尝试打开文件
    if (File)           // 判断文件是否存在
    {
        fclose(File);         // 关闭句柄
        return auxDIBImageLoadA(Filename);    // 载入位图并返回指针
    }
    return NULL;          // 如果载入失败，返回 NULL
}

//载入位图并转换成纹理
//参数：纹理指针、bmp文件名、用户指定的纹理编号
int LoadGLTextures(GLuint *texture, char *bmp_file_name, int texture_id)
{
    int Status = FALSE;         // 状态指示器
    // 创建纹理的存储空间
    AUX_RGBImageRec *TextureImage[1];
    memset(TextureImage, 0, sizeof(void *) * 1);   // 将指针设为 NULL
    // 载入位图，检查有无错误，如果位图没找到则退出
    if (TextureImage[0] = LoadBMP(bmp_file_name))
    {
        Status = TRUE;         // 将 Status 设为 TRUE
        //生成(generate)纹理
        glGenTextures(texture_id, texture); //&texture[0]);     
        //绑定2D纹理对象
        glBindTexture(GL_TEXTURE_2D, *texture); //texture[0]);
        //关联图像数据与纹理对象
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        //图形绘制时所使用的滤波器参数
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线形滤波
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 线形滤波
    }

    //释放图像的内存，因为已经生成纹理了，没用了
    if (TextureImage[0])        // 纹理是否存在
    {
        if (TextureImage[0]->data)      // 纹理图像是否存在
        {
            free(TextureImage[0]->data);    // 释放纹理图像占用的内存
        }
        free(TextureImage[0]);       // 释放图像结构
    }
    else
        printf("纹理不存在");
    return Status;          // 返回 Status
}

void DrawCube(void)         // 从这里开始进行所有的绘制
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清除屏幕和深度缓存
    glLoadIdentity();         // 重置当前的模型观察矩阵
    glTranslatef(0.0f, 0.0f, -5.0f);         // 移入屏幕 5 个单位
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);         // 绕X轴旋转
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);         // 绕Y轴旋转
    glRotatef(zrot, 0.0f, 0.0f, 1.0f);         // 绕Z轴旋转
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);      // 选择纹理
    glBegin(GL_QUADS);
    // 前面
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
    // 后面
    glEnd();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
    // 顶面
    glEnd();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    // 底面
    glEnd();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    // 右面
    glEnd();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // 纹理和四边形的左上
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f); // 纹理和四边形的左下
    // 左面
    glEnd();
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // 纹理和四边形的左下
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // 纹理和四边形的右下
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // 纹理和四边形的右上
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // 纹理和四边形的左上
    glEnd();

    glFlush(); //glutSwapBuffers();
}

float Mysecond(struct tm *ptr)
{
    return((Pi / 2) - (((float)ptr->tm_sec) / 60) * 2 * Pi);
}

float Mymin(struct tm *ptr)
{
    return((Pi / 2) - ((ptr->tm_min + (Mysecond(ptr) / 60)) / 60) * 2 * Pi);
}

float Myhour(struct tm *ptr)
{
    if (0 < ptr->tm_hour&&ptr->tm_hour < 12)
    {
        return((Pi / 2) - ((float)ptr->tm_hour + Mymin(ptr) / 60.0) / 12.0 * 2 * Pi);
    }
    else{
        return((Pi / 2) - ((ptr->tm_hour - 12.0 + Mymin(ptr) / 60.0) / 12) * 2 * Pi);
    }
}

void myDisplay(void)
{
    struct tm *ptr;  //获取系统时间
    time_t it;
    it = time(NULL);
    ptr = localtime(&it);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    DrawCube();//钟盘
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glTranslatef(0, -0.0, 1.0);
    glColor4f(1.0, 0.0, 0.0, 0.5);  //洋红色
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++){
        glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
    }
    glEnd();

    //刻度
    glColor4f(1.0, 1.0, 1.0, 0.5);  //白色
    glBegin(GL_POINTS);
    glPointSize(5.0f);
    for (int j = 0; j < 12; j++)
    {
        glVertex2f(0.75*cos(2 * Pi / 12 * j), 0.75*sin(2 * Pi / 12 * j));
    }
    glEnd();

    //表盘上的中心点
    glPointSize(5.0f);
    glColor4f(0.0, 0.0, 0.0, 0.2);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();

    //时针
    glLineWidth(5.0f);  //设置线的宽度
    glColor4f(1.0, 0.0, 1.0, 0.5);  //洋红色
    glBegin(GL_LINES);  //画线函数
    glRotatef((angle / 3600.0), 0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(cos(Myhour(ptr))*R*0.55, sin(Myhour(ptr))*R*0.55);
    glEnd();

    //分针
    glLineWidth(5.0f);
    glColor4f(0.0, 1.0, 0.0, 0.5);  //绿色
    glBegin(GL_LINES);
    glRotatef((angle / 60.0), 0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(cos(Mymin(ptr))*R*0.65, sin(Mymin(ptr))*R*0.65);
    glEnd();

    //秒针
    glLineWidth(3.0f);
    glColor4f(0.0, 0.0, 1.0, 0.5);  //蓝色
    glBegin(GL_LINES);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(cos(Mysecond(ptr))*R*0.85, sin(Mysecond(ptr))*R*0.85);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();//    glFlush();  //保证前面的OpenGL命令立即执行，而不是让它们在缓冲区中等待
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  //清理颜色，为白色，（也可认为是背景颜色）
    glCullFace(GL_BACK);
    //背面裁剪(背面不可见)
    glEnable(GL_CULL_FACE);
    //启用裁剪
    glEnable(GL_TEXTURE_2D);
    LoadGLTextures(&texture[0], "clock3.bmp", 1);            //载入纹理贴图
    LoadGLTextures(&texture[1], "clock3.bmp", 2);
}

//当窗口大小改变时，会调用这个函数
void reshape(GLsizei w, GLsizei h)
{
    //这里小说明一下：矩阵模式是不同的，他们各自有一个矩阵。投影相关
    //只能用投影矩阵。
    glViewport(0, 0, w, h);        //设置视口
    glMatrixMode(GL_PROJECTION);    //设置矩阵模式为投影变换矩阵，
    glLoadIdentity();                //变为单位矩阵
    gluPerspective(60, (GLfloat)w / h, 0, 1000);    //设置投影矩阵
    glMatrixMode(GL_MODELVIEW);        //设置矩阵模式为视图矩阵(模型)
    glLoadIdentity();                //变为单位矩阵
}

//键盘输入事件函数
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':    //当按下键盘上d时，以沿X轴旋转为主
        xrot += 6.0f;   //设置旋转增量
        glutPostRedisplay();   //重绘函数
        break;
    case 'y':
        yrot += 6.0f;
        glutPostRedisplay();
        break;
    case 'z':
        zrot += 6.0f;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

void myIdle(void)
{
    angle -= ((2 * Pi) / 60);
    Sleep(1000);
    if (angle < 0.0f){
        angle = 2 * Pi;
    }
    myDisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);  //对GLUT进行初始化
    //    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);  //设置显示方式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//设置双缓存
    //GLUT_RGB表示使用RGB颜色，GLUT_SINGLE表示使用单缓冲
    glutInitWindowPosition(200, 200);  //设置窗口在屏幕中的位置
    glutInitWindowSize(500, 500);  //设置窗口的大小
    glutCreateWindow("OpenGL时钟");  //设置窗口的标题
    init();  //初始化资源,这里一定要在创建窗口以后，不然会无效。
    LoadGLTextures(&texture[0], "clock3.bmp", 1);
    LoadGLTextures(&texture[1], "clock3.bmp", 2);
    glutDisplayFunc(&myDisplay);  //调用画图函数
    glutIdleFunc(&myIdle);
    glutReshapeFunc(reshape);                //绘制图形时的回调
    glutKeyboardFunc(keyboard);
    glutMainLoop();  //进行一个消息循环。显示窗口，并等待窗口关闭后才会返回

    return 0;
}