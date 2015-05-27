#include "Fun.h"



/* ResizeGlscene 函数负责重置一个opengl视口。
   以所创建窗口左下角为坐标原点， (x,y) 为opengl视口的左下角 width height 分别为视口的宽和高
   opengl 会在该视口内进行绘图
   函数会重置投影矩阵
   函数调用 gluPerspective() 重置视景体的大小 far 为视景体最远距离
   函数重置观察矩阵
*/
void ReSizeGLScene( GLsizei x, GLsizei y, GLsizei width, GLsizei height, GLdouble gNear, GLdouble gfar)//重置一个OpenGl视口
{
	if (height==0)										              //防止高度变为0，此后高度将作为分母出现
	{
		height = 1 ;
	}

	glViewport( x, y, width, height) ;					              //重置当前视口

	glMatrixMode(GL_PROJECTION);						              //选择投影矩阵
	glLoadIdentity();									              //重置投影矩阵


	gluPerspective( 45, (GLfloat)width/(GLfloat)height, gNear, gfar) ;//设置视景体的大小

	glMatrixMode(GL_MODELVIEW);							              //选择模型观察矩阵
	glLoadIdentity();									              //重置模型观察矩阵

}


GLUquadricObj *InitGL(void)//初始化着色模式、背景色、深度缓存设置、透视修正
{
    GLUquadricObj *qua ;                                //用于存储二次对象


	glShadeModel(GL_SMOOTH);							//启用阴影平滑
	glClearColor( 0, 0, 0, 0) ;				            //设置背景色为黑
	glClearDepth(1);									//设置深度缓存
	glEnable(GL_DEPTH_TEST);							//启用深度测试
	glDepthFunc(GL_LEQUAL);								//所做深度测试的类型
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST) ;//告诉系统对透视进行修正
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);		            //基于源象素alpha通道值的半透明混合函数
    glLineWidth(0.01) ;                                 //设定线条宽度
    qua = gluNewQuadric() ;				                //创建二次几何体
    gluQuadricNormals( qua, GLU_SMOOTH);		        //使用平滑法线
    gluQuadricTexture( qua, GL_TRUE);		            //使用纹理

	//告诉opengl以显示效果为重，速度不重要
	//glHint( GL_POINT_SMOOTH, GL_NICEST) ;             //开启点平滑
	//glEnable(GL_POINT_SMOOTH);

	//glHint( GL_LINE_SMOOTH, GL_NICEST) ;              //开启线平滑
	//glEnable(GL_LINE_SMOOTH);

	//glHint( GL_POLYGON_SMOOTH, GL_NICEST) ;           //开启面平滑
	//glEnable(GL_POLYGON_SMOOTH);

	return qua ;                                        //返回二次曲面对象
}


void KillGLWindow(HWND *hwnd, HDC *hdc, HGLRC *hrc)//释放DC和RC，删除RC和DC
{
	if (*hrc)											//拥有OpenGl渲染（着色）描述表么？
	{
		if (!wglMakeCurrent( NULL, NULL))				//是否成功释放DC和RC描述表？
		{
		    ErrorBox("Release Of DC And RC Failed.");
		}

		if (!wglDeleteContext(*hrc))					//是否成功删除RC描述表？
		{
		    ErrorBox("Release Rendering Context Failed.");
		}

		*hrc = NULL ;									//将RC设为 NULL
	}

	if (*hdc && !ReleaseDC( *hwnd, *hdc))				//是否成功释放DC？
	{
	    ErrorBox("Release Device Context Failed.");
		*hdc = NULL ;									//将DC设为 NULL
	}
}


BOOL CreateGLWindow( char* ClassName, char* WindowName, int width, int height, HWND *hwnd)//创建窗口
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
        return TRUE ;									//创建成功返回 TRUE
    }
    else
    {
        return FALSE ;
    }
}


int GlRelateWindow( HWND *hwnd, HDC *hdc, HGLRC *hrc)//将windows窗口与OpenGl相关联
{
    GLuint		PixelFormat;			            //保存查找匹配的结果
	PIXELFORMATDESCRIPTOR pfd =			            //pfd 告诉窗口我们所希望的像素格式
	{
		sizeof(PIXELFORMATDESCRIPTOR),				//PIXELFORMATDESCRIPTOR结构体的大小
		1,											//版本号
		PFD_DRAW_TO_WINDOW |						//格式支持窗口
		PFD_SUPPORT_OPENGL |						//格式必须支持OpenGl
		PFD_DOUBLEBUFFER,							//必须支持双缓冲
		PFD_TYPE_RGBA,								//申请RGBA格式
		32,										    //选定色彩深度
		0, 0, 0, 0, 0, 0,							//忽略的色彩位
		0,											//无Alpha缓存
		0,											//忽略shift bit
		0,											//无累加缓存
		0, 0, 0, 0,									//忽略聚集位
		16,											//16位 Z—缓存 （深度缓存）
		0,											//无蒙版缓存
		0,											//无辅助缓存
		PFD_MAIN_PLANE,								//主绘图层
		0,											//Reserved
		0, 0, 0										//忽略层遮罩
	} ;


    //如果前面创建窗口时没有错误发生，我们接着尝试取得OpenGL设备描述表。若无法取得DC，弹出错误消息程序退出(返回FALSE)。
	if (!(*hdc=GetDC(*hwnd)))						        //取得设备描述表了么？
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Create A GL Device Context.");
		return FALSE ;								        //返回 False
	}


    //设法为OpenGL窗口取得设备描述表后，我们尝试找到对应与此前我们选定的象素格式的象素格式。
	if (!(PixelFormat = ChoosePixelFormat( *hdc, &pfd)))	//Windows 找到相应的像素格式了么？
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Find A Suitable PixelFormat.");
		return FALSE ;								        //返回 FALSE
	}


    //Windows 找到相应的象素格式后，尝试设置象素格式。如果无法设置，弹出错误消息，并退出程序(返回FALSE)。
	if(!SetPixelFormat( *hdc, PixelFormat, &pfd))		    //能够设置像素格式么？
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Set The PixelFormat.");
		return FALSE ;								        //返回 FALSE
	}


    //正常设置象素格式后，尝试取得着色描述表。如果不能取得着色描述表的话，弹出错误消息，并退出程序(返回FALSE)。
	if (!(*hrc = wglCreateContext(*hdc)))				    //能否取得着色描述表？
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Create A GL Rendering Context.");
		return FALSE ;								        //返回FALSE
	}


    //如果到现在仍未出现错误的话，我们已经设法取得了设备描述表和着色描述表。
    //接着要做的是激活着色描述表。如果无法激活，弹出错误消息，并退出程序(返回FALSE)。
	if(!wglMakeCurrent( *hdc, *hrc))					    //尝试激活着色描述表
	{
		KillGLWindow( hwnd, hdc, hrc) ;
		ErrorBox("Can't Activate The GL Rendering Context.");
		return FALSE ;								        //返回 FALSE
	}


    //一切顺利的话，OpenGL窗口已经创建完成，接着可以显示它啦。将它设为前端窗口(给它更高的优先级)，并将焦点移至此窗口。
    //然后调用ReSizeGLScene 将屏幕的宽度和高度设置给透视OpenGL屏幕。
	ShowWindow( *hwnd, SW_SHOW) ;					        // 显示窗口
    UpdateWindow(*hwnd);

    return TRUE ;
}
