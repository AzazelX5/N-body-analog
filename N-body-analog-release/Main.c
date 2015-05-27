#include "Fun.h"


HWND    hScreenWindow = NULL ;//显示窗口句柄
HWND      hDrawWindow = NULL ;//绘图窗口句柄
HWND  hComputerWindow = NULL ;//计算窗口句柄
HWND   hInfoBarWindow = NULL ;//信息窗口句柄
HGLRC             hRC = NULL ;//着色描述表
HDC               hDC = NULL ;//设备描述表
BOOL          bPause = FALSE ;//是否处于计算状态 TRUE 表示处在暂停状态
BOOL          bDrawCs =FALSE ;//是否绘制坐标系 TRUE 表示绘制坐标系
BOOL             bMod = TRUE ;//用于监视当前是否处于默认模式 TRUE 表示处在默认状态
BOOL       bDrawOrbit = TRUE ;//用于标识是否绘制轨道 TRUE 表示绘制轨道
BOOL    CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);     //定义对话框过程函数
char   sAppName[] = "N-Body" ;//程序的名称


int     iWidth = 1024, iHeight = 576 ;//用于存储显示窗口的大小
int       iPlanetNumber = -1         ;//当前观察中心的行星编号 -1 代表坐标系中心
char sPlaInfoFileName[] = "info.dat" ;//读取行星信息文件的名字
GLdouble        gldXrot = 45         ;//x 轴旋转的角度
GLdouble        gldYrot = -45        ;//y 轴旋转的角度
GLdouble        gldDeep = -1         ;//深入屏幕的距离


Planet      *PlanetInfo ;             //用于指向存储行星信息的链表的指
GLUquadricObj *gluQua   ;             //用于存储二次曲面对象
GLuint gluTexture[10]    ;            //用于存贮纹理
GLdouble dFar = 1E10    ;             //设定视景体的最远值
GLdouble dNear = 5   ;             //设定视景体的最近值
WORLD WorldInfo         ;             //各种参数
TCHAR szAppName[] = TEXT("MENU1");


/////////////////////////////////////////////////////////////////////////////////////////////

void DrawGLScene(void)//绘图函数
{
    Planet *Info = PlanetInfo ;                                //创建一个 Info 指针用于后续操作而不改变 PlanetInfo 的信息
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;      //清除屏幕和深度缓存

    Whirl( &gldXrot, &gldYrot, &gldDeep, Info, iPlanetNumber, dNear, dFar) ;//调整视角

    if(bDrawCs)                                                //根据 bDrawCs 的值决定是否绘制坐标系
    {
        DrawCS(WorldInfo.Multiply);                            //在世界坐标中心，绘制一个直角坐标系
    }

    if(!bMod)                                                  //根据 bMod 的值决定是否绘制默认 demo
    {                                                          //此时绘制从文件中读入的行星数据
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)             //绘制行星
        {
            DrawPlanet(Info);                                  //绘制行星
            Info = Info->next ;                                //切换到下一个行星
        }
    }
    else
    {                                                          //此时绘制默认的 demo
        DrawSun( Info, gluQua, &gluTexture[0], bPause) ;       //绘制太阳

        GLfloat lPos[]= { Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0], 1 } ;// 光源位置 始终在太阳中心
        GLfloat lDif[]= { 1, 1, 1, 1} ;  				                                //漫射光参数
        GLfloat lamb[] = { 1, 1, 1, 1} ;                                                //全局环境光设置
        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lamb) ;   //设置全局环境光
        glLightfv( GL_LIGHT0, GL_DIFFUSE, lDif) ;         //设置环境光
        glLightfv( GL_LIGHT0, GL_POSITION, lPos) ;        //设置光源位置
        glEnable(GL_LIGHT0);                              //启用 0 号光源

        Info = Info->next ;                                 //切换到下一个行星
        glEnable(GL_LIGHTING);                              //开启光源
        DrawMercury( Info, gluQua, &gluTexture[1], bPause) ;//绘制水星
        Info = Info->next ;                                 //切换到下一个行星
        DrawVenus( Info, gluQua, &gluTexture[2], bPause) ;  //绘制金星
        Info = Info->next ;                                 //切换到下一个行星
        DrawEarth( Info, gluQua, &gluTexture[3], bPause) ;  //绘制地球
        Info = Info->next ;                                 //切换到下一个行星
        DrawMars( Info, gluQua, &gluTexture[4], bPause) ;   //绘制火星
        Info = Info->next ;                                 //切换到下一个行星
        DrawJupiter( Info, gluQua, &gluTexture[5], bPause) ;//绘制木星
        Info = Info->next ;                                 //切换到下一个行星
        DrawSaturn( Info, gluQua, &gluTexture[6], bPause) ; //绘制土星
        Info = Info->next ;                                 //切换到下一个行星
        DrawUranus( Info, gluQua, &gluTexture[7], bPause) ; //绘制天王
        Info = Info->next ;                                 //切换到下一个行星
        DrawNeptune( Info, gluQua, &gluTexture[8], bPause) ;//绘制海王
        Info = Info->next ;                                 //切换到下一个行星
        DrawMoon( Info, gluQua, &gluTexture[9], bPause) ;   //绘制月球
        glDisable(GL_LIGHTING);                             //关闭光源

        Info = Info->next ;                               //切换到下一个行星

    }

    if(bDrawOrbit)                                        //根据 bDrawOrbit 的值决定是否绘制轨迹
    {
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)
        {
            DrawOrbit( Info, WorldInfo.Orbit) ;           //绘制行星轨迹
            Info = Info->next ;
        }
    }

    if(!bPause)                                           //根据 bPause 判断是否处于暂停状态
    {                                                     //如果没有处在暂停状态
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)
        {
            Info->orbit = Info->orbit->next ;             //将当前轨迹点向后移动
            SaveOrbit(Info);                              //将行星状态保存入轨迹链表
            Info = Info->next ;                           //切换到下一个行星
        }
    }

    SwapBuffers(hDC);                                     //交换双重缓冲区


}


LRESULT CALLBACK ScreenWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//显示窗口过程函数
{
    static POINT mousepoint_pt[2] ;//用于存储当前鼠标位置与上次鼠标位置，第一个用来存储上一次的鼠标位置，第二个存储当前鼠标位置

    static HINSTANCE hInstance;

	switch (msg)//消息处理
	{
        case WM_CREATE://当窗口创建时
            {
                SetTimer( hwnd, 1, 40, NULL) ;

                WorldInfo = GetPlaNum(sPlaInfoFileName) ;//从文件中获取初始信息

                if(WorldInfo.PlanetQty > 0)//当正常打开文件读取信息时
                {
                    bMod = FALSE ;//进入非 demo 模式
                    gldDeep = -5*WorldInfo.Multiply ;
                    PlanetInfo = CreateInfoLs( WorldInfo.PlanetQty, WorldInfo.Orbit) ;//创建长度与行星数量相等的链表
                    GetPlaInfo( PlanetInfo, sPlaInfoFileName, WorldInfo.PlanetQty) ;  //从文件中读取出行星的信息
                    SetZero( PlanetInfo, WorldInfo.PlanetQty, WorldInfo.Orbit) ;      //对轨迹链表进行初始化
                }
                else
                {
                    bMod = TRUE ;                                                     //进入 demo 模式
                    iPlanetNumber = -1 ;                                              //设定观察中心为指定编号
                    gldDeep = -3000 ;                                                 //设定视角深度
                    gldXrot = 0, gldYrot = -180 ;                                     //x y轴旋转的角度
                    SetDefaultWorld(&WorldInfo);                                      //设定默认的世界数值
                    PlanetInfo = CreateInfoLs( WorldInfo.PlanetQty, WorldInfo.Orbit) ;//创建长度与行星数量相等的链表
                    SetDefaultInfo(PlanetInfo);                                       //设定默认值
                    SetZero( PlanetInfo, WorldInfo.PlanetQty, WorldInfo.Orbit) ;      //对轨迹链表进行初始化
                }
                _beginthread( Draw, 0, NULL) ;                                        //创建绘图线程
                _beginthread( Computer, 0, NULL) ;                                    //创建计算线程

                hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
                return 0 ;
            }

        case WM_TIMER:
            {

                return 0 ;
            }

        case WM_MOUSEWHEEL://处理鼠标滚轮消息
            {
                switch(HIWORD(wParam))
                {
                    case 120: gldDeep -= 0.5*gldDeep ;break;
                    case 65416: gldDeep += 0.5*gldDeep ;break;
                }
                return 0 ;
            }

        case WM_LBUTTONDOWN://当右键按下时
            {
                //获取鼠标的当前位置
                mousepoint_pt[0].x = LOWORD(lParam) ;
                mousepoint_pt[0].y = HIWORD(lParam) ;

                return 0 ;
            }

        case WM_MOUSEMOVE://鼠标移动时
            {
                if(wParam&MK_LBUTTON)  //若鼠标移动时右键按下
                {
                    //获取当前鼠标位置
                    mousepoint_pt[1].x = LOWORD(lParam) ;
                    mousepoint_pt[1].y = HIWORD(lParam) ;

                    //计算视角旋转的角度
                    gldYrot -= 0.5*(mousepoint_pt[0].x - mousepoint_pt[1].x) ;
                    gldXrot += 0.5*(mousepoint_pt[1].y - mousepoint_pt[0].y) ;

                    //计算完毕，将旧的鼠标位置改变为当前鼠标位置，以进行后续运算
                    mousepoint_pt[0].x = mousepoint_pt[1].x ;
                    mousepoint_pt[0].y = mousepoint_pt[1].y ;
                }

                return 0 ;
            }

        case WM_KEYDOWN://有按键按下
            {
                switch(wParam)
                {
                    case VK_SPACE://当空格被按下时
                        {
                            bPause = !bPause ;//反转暂停状态
                            break;
                        }

                    case VK_B://当 B 被按下时
                        {
                            bDrawOrbit = !bDrawOrbit ;//反转绘制轨迹的状态
                            break;
                        }

                    case VK_C://当C被按下时
                        {
                            bDrawCs = !bDrawCs ;//反转绘制坐标系的状态
                            break;
                        }

                    case VK_Q://当Q被按下时
                        {
                            iPlanetNumber += 1 ;
                            if(iPlanetNumber==WorldInfo.PlanetQty)//若当前坐标中心的行星编号超过现有行星编号
                            {
                                iPlanetNumber = -1 ;//使当前观察行星编号设为坐标系中心
                            }
                            break;
                        }

                    case VK_E://当E被按下时
                        {
                            iPlanetNumber -=1 ;
                            if(iPlanetNumber<=-2)
                            {
                                iPlanetNumber = WorldInfo.PlanetQty - 1 ;
                            }
                            break;
                        }

                    case VK_A:
                        {
                            SendMessage( hDrawWindow, WM_SAVEBMP, 0, 0) ;
                            break;
                        }
                }

                return 0 ;
            }

        case WM_SIZE://窗口大小发生变化
            {
                SendMessage( hDrawWindow, WM_SIZE, wParam, lParam) ;//将新的尺寸传递给绘图窗口过程，以进行视口的重置
                return 0 ;
            }

        case WM_CLOSE://收到关闭窗口消息
            {
                SendMessage( hDrawWindow, WM_CLOSE, 0, 0) ;    //发送WM_CLOSE至绘图窗口过程，以清除相应资源
                return 0 ;
            }

        case WM_DESTROY://销毁窗口
            {
                PostQuitMessage(0);
                return 0 ;
            }

        case WM_COMMAND:
		switch (LOWORD(wParam))
		{
                case ID_SP:
                        {
                            bPause = !bPause ;//反转暂停状态
                            break;
                        }


		case ID_Exit:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;

                case ID_ShowHideC:
                        {
                            bDrawCs = !bDrawCs ;//反转绘制坐标系的状态
                            break;
                        }

                case ID_ShowHideB:
                        {
                            bDrawOrbit = !bDrawOrbit ;//反转绘制轨迹的状态
                            break;
                        }

                case ID_ChangeQ:
                         {
                            iPlanetNumber += 1 ;
                            if(iPlanetNumber==WorldInfo.PlanetQty)//若当前坐标中心的行星编号超过现有行星编号
                            {
                                iPlanetNumber = -1 ;//使当前观察行星编号设为坐标系中心
                            }
                            break;
                        }

                case ID_ChangeE:
                        {
                            iPlanetNumber -=1 ;
                            if(iPlanetNumber<=-2)
                            {
                                iPlanetNumber = WorldInfo.PlanetQty - 1 ;
                            }
                            break;
                        }



                case ID_Screenshots:
                         {
                            SendMessage( hDrawWindow, WM_SAVEBMP, 0, 0) ;
                            break;
                        }

                case ID_FUNCTION:
                        DialogBox(hInstance, TEXT("FUNCTION"), hwnd, AboutDlgProc);
			 break;

		case ID_ABOUT:
			DialogBox(hInstance, TEXT("About"), hwnd, AboutDlgProc);
			 break;
		}
		break;
	}

	return DefWindowProc( hwnd, msg, wParam, lParam) ;// 向DefWindowProc传递未处理的信息
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam) //对话框过程
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		    EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
        case WM_CLOSE:
                EndDialog(hDlg, 0);
                return TRUE;
	}
	return FALSE;
}





int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)//程序入口
{
	MSG		   msg ;// 窗口消息结构体
    WNDCLASS	wc ;// 窗口类结构体

	wc.style		 = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;	             //大小改变时重画窗口，为窗口取得DC
	wc.lpfnWndProc	 = (WNDPROC)ScreenWindow ;				             //指定窗口过程函数
	wc.cbClsExtra	 = 0 ;
	wc.cbWndExtra	 = 0 ;
	wc.hInstance   	 = hInstance ;                                       //窗口实例代号
	wc.hIcon		 = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1)) ;//程序图标
	wc.hCursor		 = LoadCursor( NULL, IDC_ARROW) ;                    //载入默认鼠标图标
	wc.hbrBackground = NULL ;                                            //窗口背景色
	wc.lpszMenuName	 = szAppName ;                                            //无菜单
	wc.lpszClassName = "OpenGlScreen" ;						             //设定窗口类名

	if (!RegisterClass(&wc))									         //注册窗口类
	{
	    ErrorBox("Failed to register the screen window class.");
		return 0 ;//如果注册窗口类失败则退出
	}

	if (!CreateGLWindow( "OpenGlScreen", sAppName, iWidth, iHeight, &hScreenWindow))//创建OpenGl窗口
	{
	    ErrorBox("Failed to create screen window");
		return 0 ;//若窗口创建失败则退出
	}

    while (GetMessage ( &msg, NULL, 0, 0))//构建消息循环
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

	return (msg.wParam) ;				  //退出程序
}


void Draw(PVOID pVoid)//绘图线程函数
{
    MSG         msg ; //窗口消息结构体
    WNDCLASS     wc ; //窗口类结构体

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //大小改变时重画窗口
	wc.lpfnWndProc		= (WNDPROC)DrawWindow ;					//指定窗口过程函数
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //进程实例代号
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //程序图标
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //载入鼠标图标
	wc.hbrBackground	= NULL ;                                //窗口背景色
	wc.lpszMenuName		= NULL ;                                //无菜单
	wc.lpszClassName	= "OpenGlDraw" ;						//窗口类名

	if (!RegisterClass(&wc))									//注册窗口类
	{
	    ErrorBox("Failed to register draw window class");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //窗口类注册失败则退出程序
	}


    hDrawWindow = CreateWindowEx( 0,                            //创建绘图线程所用的窗口
                                 "OpenGlDraw", "Draw",
                                 WS_POPUP, 0, 0, 0, 0,
                                 NULL, NULL,
                                 GetModuleHandle(NULL),
                                 NULL
                                 ) ;
    if(hDrawWindow==NULL)
    {
        ErrorBox("Failed to create draw window");
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //创建窗口失败则退出程序
    }

    GlRelateWindow( &hScreenWindow, &hDC, &hRC) ;               //将显示窗口与OpenGl相关联
    ReSizeGLScene( 0, 0, iWidth, iHeight, dNear, dFar) ;	    //设置透视GL屏幕

    if(bMod)                                                    //如果当前处于 demo 模式 则载入纹理
    {
        LoadGLTextures( &gluTexture[0], "data\\sun.bmp") ;      //载入太阳纹理
        LoadGLTextures( &gluTexture[1], "data\\Mercury.bmp") ;  //载入水星纹理
        LoadGLTextures( &gluTexture[2], "data\\Venus.bmp") ;    //载入金星纹理
        LoadGLTextures( &gluTexture[3], "data\\earth.bmp") ;    //载入地球纹理
        LoadGLTextures( &gluTexture[4], "data\\Mars.bmp") ;     //载入火星纹理
        LoadGLTextures( &gluTexture[5], "data\\Jupiter.bmp") ;  //载入木星纹理
        LoadGLTextures( &gluTexture[6], "data\\Saturn.bmp") ;   //载入土星纹理
        LoadGLTextures( &gluTexture[7], "data\\Uranus.bmp") ;   //载入天王纹理
        LoadGLTextures( &gluTexture[8], "data\\Neptune.bmp") ;  //载入海王纹理
        LoadGLTextures( &gluTexture[9], "data\\moon.bmp") ;     //载入月球纹理

    }

    gluQua = InitGL();                                          //初始化新建的GL窗口

    //当载入工作完成后激活 screen 窗口
    SetForegroundWindow(hScreenWindow);                         //激活 Screen 窗口
    SetFocus(hScreenWindow);                                    //将键盘焦点设置到 Screen 窗口

    while (GetMessage ( &msg, NULL, 0, 0))                      //构建消息循环
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

}


LRESULT CALLBACK DrawWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//绘图线程窗口过程函数
{

    switch(msg)  //消息处理
    {
        case WM_CREATE://窗口创建时
            {
                SetTimer( hwnd, 1, 40, NULL) ;//设定一个时钟
                return 0 ;
            }

        case WM_SAVEBMP:
            {
                SaveBmp( 0, 0, iHeight, iWidth) ;//将窗口大小传入截图函数
                return 0 ;
            }

        case WM_TIMER://收到时钟发出的消息
            {
                DrawGLScene();   //进行绘图
                return 0 ;
            }

        case WM_SIZE://收到来自显示窗口的大小改变的消息
            {
                iWidth = LOWORD(lParam) ;
                iHeight = HIWORD(lParam) ;
                ReSizeGLScene( 0, 0, iWidth, iHeight, dNear, dFar) ;//当显示窗口大小变化时，重置OpenGl视口
                return 0 ;
            }

        case WM_CLOSE://收到关闭窗口消息
            {
                KillGLWindow( &hDrawWindow, &hDC, &hRC) ;//销毁DC RC
                SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;
                return 0 ;
            }
    }
    return DefWindowProc(hwnd,msg,wParam,lParam) ;//向DefWindowProc传递未处理的信息
}


void Computer(PVOID void_pv)//计算线程函数
{
    MSG         msg ; //窗口消息结构体
    WNDCLASS     wc ; //窗口类结构体

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //大小改变时重画窗口
	wc.lpfnWndProc		= (WNDPROC)ComputerWindow ;				//指定窗口过程函数
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //进程实例代号
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //程序图标
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //载入鼠标图标
	wc.hbrBackground	= NULL ;                                //窗口背景色
	wc.lpszMenuName		= NULL ;                                //无菜单
	wc.lpszClassName	= "OpenGlComputer" ;					//窗口类名


	if (!RegisterClass(&wc))									//注册窗口类
	{
	    ErrorBox("Failed to register computer window class.");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //注册窗口类失败则退出程序
	}

    hComputerWindow = CreateWindowEx( 0,                        //创建所用的窗口
                                      "OpenGlComputer", "Computer",
                                      WS_POPUP, 0, 0, 0, 0,
                                      NULL, NULL,
                                      GetModuleHandle(NULL),
                                      NULL
                                    ) ;

	if(hComputerWindow==NULL)
    {
        ErrorBox("Failed to create computer window.");
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //创建窗口失败则退出程序
    }


    while (GetMessage ( &msg, NULL, 0, 0))                      //构建消息循环
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }


}


LRESULT CALLBACK ComputerWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//计算线程窗口过程函数
{
    switch(msg)  //消息处理
    {
        case WM_CREATE:
            {
                SetTimer( hwnd, 1, 40, NULL) ;//设置一个时钟来确定计算频率
                return 0 ;
            }

        case WM_TIMER://收到时钟发出的消息
            {
                //time_t start = time(NULL) ;

                for(int i=0; i<WorldInfo.CalRate; i++)//进行 iCalRate 次计算
                {
                    if(bPause)
                    {
                        return 0 ;
                    }
                    Calculate( PlanetInfo, WorldInfo.PlanetQty, WorldInfo.StepSize, WorldInfo.G) ;
                }
                //time_t end = time(NULL) ;
                //char stime[100] ;
                //sprintf( stime, "%lf", end-start) ;
                //TextOut( hDC, 0, 0, stime, strlen(stime)) ;

                return 0 ;
            }

    }
    return DefWindowProc(hwnd,msg,wParam,lParam) ;//向DefWindowProc传递未处理的信息

}


void InfoBar(PVOID pVoid)
{
    MSG         msg ; //窗口消息结构体
    WNDCLASS     wc ; //窗口类结构体

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //大小改变时重画窗口
	wc.lpfnWndProc		= (WNDPROC)InfoBarWindow ;				//指定窗口过程函数
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //进程实例代号
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //程序图标
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //载入鼠标图标
	wc.hbrBackground	= NULL ;                                //窗口背景色
	wc.lpszMenuName		= NULL ;                                //无菜单
	wc.lpszClassName	= "InfoBar" ;					        //窗口类名

	if (!RegisterClass(&wc))									//注册窗口类
	{
	    ErrorBox("Failed to register InfoBar window class.");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //注册窗口类失败则退出程序
	}

    hInfoBarWindow = CreateWindowEx( 0,
                                      "InfoBar", "InfoBar",
                                      WS_POPUP, 100, 100, 100, 100,
                                      NULL, NULL,
                                      GetModuleHandle(NULL),
                                      NULL
                                    ) ;

    UpdateWindow(hInfoBarWindow);
    ShowWindow( hInfoBarWindow, SW_SHOW) ;

	if(hInfoBarWindow==NULL)
    {
        ErrorBox("Failed to create infobar window.");
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //创建窗口失败则退出程序
    }



    while (GetMessage ( &msg, NULL, 0, 0))                      //构建消息循环
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

}



LRESULT CALLBACK InfoBarWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//信息栏线程窗口过程函数
{
    switch(msg)
    {
        case WM_CREATE:
            {
                SetTimer( hwnd, 1, 40, NULL) ;
                return 0 ;
            }

        case WM_PAINT:
            {

            }

    }
}











void ErrorMsg(PVOID pVoid)
{
    MessageBox( NULL, pVoid, "ERROR", MB_OK) ;
}

















