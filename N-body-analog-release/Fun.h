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


#define WM_PAUSE WM_USER+10         //�Զ���������ͣ�������Ϣ
#define WM_SAVEBMP WM_USER+11       //�Զ������ڽ�ͼ����Ϣ

typedef struct planet{
    long double r;                  //�뾶
    long double m;                  //����
	long double V[3] ;              //�����ٶȷ���
    long double x[2], y[2], z[2] ;  //��������ֵ
	long double k[4][3];            //�洢����������������� k1 k2 k3 k4 ����������
	struct planet *previous;        //ָ����һ�������ָ��
	struct planet *next;            //ָ����һ�������ָ��
	struct planet *orbit;           //ָ��켣�����ָ��
}Planet;                            //�洢���ǹ켣�Լ���Ϣ�Ľṹ��


typedef struct{
    int Multiply ;                  //�趨��������ϵ�ĵ�λ����
    int Orbit ;                     //�趨�켣��ĳ���
    int PlanetQty ;                 //��������
    double CalRate ;                //����Ƶ��
    double G ;                      //������������
    double StepSize ;               //���Ƽ��㲽��������ԽС������Խ������׼��Խ��
}WORLD;                             //���ڱ�����ֲ���




/////////////////////////



void ReSizeGLScene( GLsizei x, GLsizei y, GLsizei width, GLsizei height, GLdouble gNear, GLdouble gfar);//����һ��OpenGl�ӿ�
BOOL CreateGLWindow( char* ClassName, char* WindowName, int width, int height, HWND *hwnd);             //��������
int GlRelateWindow( HWND *hwnd, HDC *hdc, HGLRC *hrc) ;                                                 //��windows������OpenGl��������
void KillGLWindow(HWND *hwnd, HDC *hdc, HGLRC *hrc);                                                    //�ͷ�DC��RC��ɾ��RC��DC
GLUquadricObj *InitGL(void);                                                                            //��ʼ����ɫģʽ������ɫ����Ȼ������á�͸������




/////////////////////////



void Calculate( Planet *Info, int iQty, long double h, double G) ;//���ڼ���
int GetPlaInfo(Planet *Info, char sInfoFileName[], int num);      //���ļ��л�ȡ�������ݣ�������������
void SaveBmp( GLint x, GLint y, GLint height, GLint width);       //���н�ͼ
int LoadGLTextures(GLuint *texture, char *Filename);              //����λͼ��ת��������
void SetZero(Planet *Info, int num, int OrbitNum);                //�Թ켣������г�ʼ��
Planet *CreateInfoLs(int num, int OrbitNum);                      //��������Ϊi��˫��������
AUX_RGBImageRec *LoadBMP(char *Filename);                         //����λͼͼ��
void SetDefaultWorld(WORLD *WorldInfo);                           //�趨Ĭ�ϵ�������Ϣ
WORLD GetPlaNum(char sInfoFileName[]);                            //���ļ��л�ȡ��ʼ��Ϣ
void SetDefaultInfo(Planet *Info);                                //�������� info.dat �ļ�ʱ ʹ�ô˺����趨Ĭ����ֵ
void SaveOrbit(Planet *Info);                                     //����켣��



/////////////////////////////////


LRESULT CALLBACK ComputerWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;//�����̴߳��ڹ��̺���
LRESULT CALLBACK ScreenWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;  //��ʾ���ڹ��̺�����������ʾ���ջ�ͼ�������������
LRESULT CALLBACK InfoBarWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);  //��Ϣ���̴߳��ڹ��̺���
LRESULT CALLBACK DrawWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) ;    //��ͼ�̴߳��ڹ��̺��������ڻ���ͼ��
void Computer(PVOID void_pv);                                                        //�����̺߳���
void ErrorMsg(PVOID pVoid);                                                          //�����߳�
void Draw(PVOID void_pv) ;                                                           //��ͼ�̺߳���




//////////////////////


void Whirl(GLdouble *Xrot, GLdouble *Yrot, GLdouble *Deep, Planet *Info, int num, double Near, double Far);//���ڽ����ӽ���ת
void DrawNeptune(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //�ڵ�ǰλ�û���һ��������
void DrawMercury(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //�ڵ�ǰλ�û���һ��ˮ��
void DrawJupiter(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);  //�ڵ�ǰλ�û���һ��ľ��
void DrawSaturn(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);   //�ڵ�ǰλ�û���һ������
void DrawUranus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);   //�ڵ�ǰλ�û���һ��������
void DrawEarth(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);    //�ڵ�ǰλ�û���һ������
void DrawVenus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);    //�ڵ�ǰλ�û���һ������
void DrawMoon(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);     //�ڵ�ǰλ�û���һ������
void DrawMars(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);     //�ڵ�ǰλ�û���һ������
void DrawSun(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause);      //�ڵ�ǰλ�û���һ��̫��
void DrawUniverse(GLUquadricObj *qua, GLuint *texture);                           //�������汳��
void DrawArrow( GLfloat hight, GLfloat width);                                    //����һ����ͷ
void DrawOrbit(Planet *Info, int OrbitNum);                                       //�������ǹ켣
void DrawPlanet(Planet *Info);                                                    //�ڵ�ǰλ�û���һ������
void DrawCS(int length);                                                          //����һ��ֱ������ϵ



/////////////////////////



void ErrorBox(char sContent[]);                                   //���ڱ���ļ���ʾ��





#ifdef __cplusplus
}
#endif

#endif
