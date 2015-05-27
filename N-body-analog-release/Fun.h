#ifndef FUN_H_INCLUDED
#define FUN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif




#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glut.h>
#include <gl\glaux.h>
#include <process.h>
#include <math.h>
#include <time.h>
#include "resources/resource.h"


#define VK_A 65
#define VK_B 66
#define VK_C 67
#define VK_D 68
#define VK_E 69
#define VK_F 70
#define VK_Q 81


#define WM_PAUSE WM_USER+10         //自定义用于暂停计算的消息
#define WM_SAVEBMP WM_USER+11       //自定义用于截图的消息

typedef struct planet{
    long double r;                  //半径
    long double m;                  //质量
	long double V[3] ;              //三个速度分量
    long double x[2], y[2], z[2] ;  //三个坐标值
	long double k[4][3];            //存储经典龙格库塔法所用 k1 k2 k3 k4 的三个分量
	struct planet *previous;        //指向上一个链表的指针
	struct planet *next;            //指向下一个链表的指针
	struct planet *orbit;           //指向轨迹链表的指针
}Planet;                            //存储行星轨迹以及信息的结构体


typedef struct{
    int Multiply ;                  //设定整个坐标系的单位长度
    int Orbit ;                     //设定轨迹点的长度
    int PlanetQty ;                 //行星数量
    double CalRate ;                //计算频率
    double G ;                      //万有引力常量
    double StepSize ;               //控制计算步长。步长越小，计算越慢，精准度越高
}WORLD;                             //用于保存各种参数




/////////////////////////



void ReSizeGLScene( GLsizei x, GLsizei y, GLsizei width, GLsizei height, GLdouble gNear, GLdouble gfar);//重置一个OpenGl视口
BOOL CreateGLWindow( char* ClassName, char* WindowName, int width, int height, HWND *hwnd);             //创建窗口
int GlRelateWindow( HWND *hwnd, HDC *hdc, HGLRC *hrc) ;                                                 //将windows窗口与OpenGl关联起来
void KillGLWindow(HWND *hwnd, HDC *hdc, HGLRC *hrc);                                                    //释放DC和RC，删除RC和DC
GLUquadricObj *InitGL(void);                                                                            //初始化着色模式、背景色、深度缓存设置、透视修正




/////////////////////////



void Calculate( Planet *Info, int iQty, long double h, double G) ;//用于计算
int GetPlaInfo(Planet *Info, char sInfoFileName[], int num);      //从文件中获取行星数据，并存入链表中
void SaveBmp( GLint x, GLint y, GLint height, GLint width);       //进行截图
int LoadGLTextures(GLuint *texture, char *Filename);              //载入位图并转换成纹理
void SetZero(Planet *Info, int num, int OrbitNum);                //对轨迹链表进行初始化
Planet *CreateInfoLs(int num, int OrbitNum);                      //创建长度为i的双向环形链表
AUX_RGBImageRec *LoadBMP(char *Filename);                         //载入位图图象
void SetDefaultWorld(WORLD *WorldInfo);                           //设定默认的世界信息
WORLD GetPlaNum(char sInfoFileName[]);                            //从文件中获取初始信息
void SetDefaultInfo(Planet *Info);                                //当不存在 info.dat 文件时 使用此函数设定默认数值
void SaveOrbit(Planet *Info);                                     //保存轨迹点



/////////////////////////////////


LRESULT CALLBACK ComputerWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;//计算线程窗口过程函数
LRESULT CALLBACK ScreenWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;  //显示窗口过程函数，用于显示最终绘图结果，并处理交互
LRESULT CALLBACK InfoBarWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);  //信息栏线程窗口过程函数
LRESULT CALLBACK DrawWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;    //绘图线程窗口过程函数，用于绘制图像
void Computer(PVOID void_pv);                                                        //计算线程函数
void ErrorMsg(PVOID pVoid);                                                          //报错线程
void Draw(PVOID void_pv) ;                                                           //绘图线程函数




//////////////////////


void Whirl(GLdouble *Xrot, GLdouble *Yrot, GLdouble *Deep, Planet *Info, int num, double Near, double Far);//用于进行视角旋转
void DrawNeptune(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //在当前位置绘制一个海王星
void DrawMercury(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //在当前位置绘制一个水星
void DrawJupiter(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //在当前位置绘制一个木星
void DrawSaturn(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);   //在当前位置绘制一个土星
void DrawUranus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);   //在当前位置绘制一个天王星
void DrawEarth(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);    //在当前位置绘制一个地球
void DrawVenus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);    //在当前位置绘制一个金星
void DrawMoon(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);     //在当前位置绘制一个月球
void DrawMars(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);     //在当前位置绘制一个火星
void DrawSun(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);      //在当前位置绘制一个太阳
void DrawUniverse(GLUquadricObj *qua, GLuint *texture);                           //绘制宇宙背景
void DrawArrow( GLfloat hight, GLfloat width);                                    //绘制一个箭头
void DrawOrbit(Planet *Info, int OrbitNum);                                       //绘制行星轨迹
void DrawPlanet(Planet *Info);                                                    //在当前位置绘制一个行星
void DrawCS(int length);                                                          //绘制一个直角坐标系



/////////////////////////



void ErrorBox(char sContent[]);                                   //用于报错的简单提示框





#ifdef __cplusplus
}
#endif

#endif
