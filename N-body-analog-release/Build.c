#include "Fun.h"



/* ResizeGlscene ������������һ��opengl�ӿڡ�
   ���������������½�Ϊ����ԭ�㣬 (x,y) Ϊopengl�ӿڵ����½� width height �ֱ�Ϊ�ӿڵĿ�͸�
   opengl ���ڸ��ӿ��ڽ��л�ͼ
   ����������ͶӰ����
   �������� gluPerspective() �����Ӿ���Ĵ�С far Ϊ�Ӿ�����Զ����
   �������ù۲����
*/
void ReSizeGLScene( GLsizei x, GLsizei y, GLsizei width, GLsizei height, GLdouble gNear, GLdouble gfar)//����һ��OpenGl�ӿ�
{
	if (height==0)										              //��ֹ�߶ȱ�Ϊ0���˺�߶Ƚ���Ϊ��ĸ����
	{
		height = 1 ;
	}

	glViewport( x, y, width, height) ;					              //���õ�ǰ�ӿ�

	glMatrixMode(GL_PROJECTION);						              //ѡ��ͶӰ����
	glLoadIdentity();									              //����ͶӰ����


	gluPerspective( 45, (GLfloat)width/(GLfloat)height, gNear, gfar) ;//�����Ӿ���Ĵ�С

	glMatrixMode(GL_MODELVIEW);							              //ѡ��ģ�͹۲����
	glLoadIdentity();									              //����ģ�͹۲����

}


GLUquadricObj *InitGL(void)//��ʼ����ɫģʽ������ɫ����Ȼ������á�͸������
{
    GLUquadricObj *qua ;                                //���ڴ洢���ζ���


	glShadeModel(GL_SMOOTH);							//������Ӱƽ��
	glClearColor( 0, 0, 0, 0) ;				            //���ñ���ɫΪ��
	glClearDepth(1);									//������Ȼ���
	glEnable(GL_DEPTH_TEST);							//������Ȳ���
	glDepthFunc(GL_LEQUAL);								//������Ȳ��Ե�����
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) ;//����ϵͳ��͸�ӽ�������
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);		            //����Դ����alphaͨ��ֵ�İ�͸����Ϻ���
    glLineWidth(0.01) ;                                 //�趨�������
    qua = gluNewQuadric() ;				                //�������μ�����
    gluQuadricNormals( qua, GLU_SMOOTH);		        //ʹ��ƽ������
    gluQuadricTexture( qua, GL_TRUE);		            //ʹ������

	//����opengl����ʾЧ��Ϊ�أ��ٶȲ���Ҫ
	//glHint( GL_POINT_SMOOTH, GL_NICEST) ;             //������ƽ��
	//glEnable(GL_POINT_SMOOTH);

	//glHint( GL_LINE_SMOOTH, GL_NICEST) ;              //������ƽ��
	//glEnable(GL_LINE_SMOOTH);

	//glHint( GL_POLYGON_SMOOTH, GL_NICEST) ;           //������ƽ��
	//glEnable(GL_POLYGON_SMOOTH);

	return qua ;                                        //���ض����������
}


void KillGLWindow(HWND *hwnd, HDC *hdc, HGLRC *hrc)//�ͷ�DC��RC��ɾ��RC��DC
{
	if (*hrc)											//ӵ��OpenGl��Ⱦ����ɫ��������ô��
	{
		if (!wglMakeCurrent( NULL, NULL))				//�Ƿ�ɹ��ͷ�DC��RC������
		{
		    ErrorBox("Release Of DC And RC Failed.");
		}

		if (!wglDeleteContext(*hrc))					//�Ƿ�ɹ�ɾ��RC������
		{
		    ErrorBox("Release Rendering Context Failed.");
		}

		*hrc = NULL ;									//��RC��Ϊ NULL
	}

	if (*hdc && !ReleaseDC( *hwnd, *hdc))				//�Ƿ�ɹ��ͷ�DC��
	{
	    ErrorBox("Release Device Context Failed.");
		*hdc = NULL ;									//��DC��Ϊ NULL
	}
}


BOOL CreateGLWindow( char* ClassName, char* WindowName, int width, int height, HWND *hwnd)//��������
{

	*hwnd = CreateWindowEx(	WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
                            ClassName,
                            WindowName,
                            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                            0, 0, width, height,
                            NULL, NULL,
                            GetModuleHandle(NULL),
                            NULL
                            ) ;
    if(*hwnd)
    {
        return TRUE ;									//�����ɹ����� TRUE
    }
    else
    {
        return FALSE ;
    }
}


int GlRelateWindow( HWND *hwnd, HDC *hdc, HGLRC *hrc)//��windows������OpenGl�����
{
    GLuint		PixelFormat;			            //�������ƥ��Ľ��
	PIXELFORMATDESCRIPTOR pfd =			            //pfd ���ߴ���������ϣ�������ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),				//PIXELFORMATDESCRIPTOR�ṹ��Ĵ�С
		1,											//�汾��
		PFD_DRAW_TO_WINDOW |						//��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						//��ʽ����֧��OpenGl
		PFD_DOUBLEBUFFER,							//����֧��˫����
		PFD_TYPE_RGBA,								//����RGBA��ʽ
		32,										    //ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,							//���Ե�ɫ��λ
		0,											//��Alpha����
		0,											//����shift bit
		0,											//���ۼӻ���
		0, 0, 0, 0,									//���Ծۼ�λ
		16,											//16λ Z������ ����Ȼ��棩
		0,											//���ɰ滺��
		0,											//�޸�������
		PFD_MAIN_PLANE,								//����ͼ��
		0,											//Reserved
		0, 0, 0										//���Բ�����
	} ;


    //���ǰ�洴������ʱû�д����������ǽ��ų���ȡ��OpenGL�豸���������޷�ȡ��DC������������Ϣ�����˳�(����FALSE)��
	if (!(*hdc=GetDC(*hwnd)))						        //ȡ���豸��������ô��
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Create A GL Device Context.");
		return FALSE ;								        //���� False
	}


    //�跨ΪOpenGL����ȡ���豸����������ǳ����ҵ���Ӧ���ǰ����ѡ�������ظ�ʽ�����ظ�ʽ��
	if (!(PixelFormat = ChoosePixelFormat( *hdc, &pfd)))	//Windows �ҵ���Ӧ�����ظ�ʽ��ô��
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Find A Suitable PixelFormat.");
		return FALSE ;								        //���� FALSE
	}


    //Windows �ҵ���Ӧ�����ظ�ʽ�󣬳����������ظ�ʽ������޷����ã�����������Ϣ�����˳�����(����FALSE)��
	if(!SetPixelFormat( *hdc, PixelFormat, &pfd))		    //�ܹ��������ظ�ʽô��
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Set The PixelFormat.");
		return FALSE ;								        //���� FALSE
	}


    //�����������ظ�ʽ�󣬳���ȡ����ɫ�������������ȡ����ɫ������Ļ�������������Ϣ�����˳�����(����FALSE)��
	if (!(*hrc = wglCreateContext(*hdc)))				    //�ܷ�ȡ����ɫ������
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Create A GL Rendering Context.");
		return FALSE ;								        //����FALSE
	}


    //�����������δ���ִ���Ļ��������Ѿ��跨ȡ�����豸���������ɫ������
    //����Ҫ�����Ǽ�����ɫ����������޷��������������Ϣ�����˳�����(����FALSE)��
	if(!wglMakeCurrent( *hdc, *hrc))					    //���Լ�����ɫ������
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Activate The GL Rendering Context.");
		return FALSE ;								        //���� FALSE
	}


    //һ��˳���Ļ���OpenGL�����Ѿ�������ɣ����ſ�����ʾ������������Ϊǰ�˴���(�������ߵ����ȼ�)���������������˴��ڡ�
    //Ȼ�����ReSizeGLScene ����Ļ�Ŀ�Ⱥ͸߶����ø�͸��OpenGL��Ļ��
	ShowWindow( *hwnd, SW_SHOW) ;					        // ��ʾ����
    UpdateWindow(*hwnd);

    return TRUE ;
}
