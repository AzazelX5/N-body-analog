#include "Fun.h"


HWND    hScreenWindow = NULL ;//��ʾ���ھ��
HWND      hDrawWindow = NULL ;//��ͼ���ھ��
HWND  hComputerWindow = NULL ;//���㴰�ھ��
HWND   hInfoBarWindow = NULL ;//��Ϣ���ھ��
HGLRC             hRC = NULL ;//��ɫ������
HDC               hDC = NULL ;//�豸������
BOOL          bPause = FALSE ;//�Ƿ��ڼ���״̬ TRUE ��ʾ������ͣ״̬
BOOL          bDrawCs =FALSE ;//�Ƿ��������ϵ TRUE ��ʾ��������ϵ
BOOL             bMod = TRUE ;//���ڼ��ӵ�ǰ�Ƿ���Ĭ��ģʽ TRUE ��ʾ����Ĭ��״̬
BOOL       bDrawOrbit = TRUE ;//���ڱ�ʶ�Ƿ���ƹ�� TRUE ��ʾ���ƹ��
BOOL    CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);     //����Ի�����̺���
char   sAppName[] = "N-Body" ;//���������


int     iWidth = 1024, iHeight = 576 ;//���ڴ洢��ʾ���ڵĴ�С
int       iPlanetNumber = -1         ;//��ǰ�۲����ĵ����Ǳ�� -1 ��������ϵ����
char sPlaInfoFileName[] = "info.dat" ;//��ȡ������Ϣ�ļ�������
GLdouble        gldXrot = 45         ;//x ����ת�ĽǶ�
GLdouble        gldYrot = -45        ;//y ����ת�ĽǶ�
GLdouble        gldDeep = -1         ;//������Ļ�ľ���


Planet      *PlanetInfo ;             //����ָ��洢������Ϣ�������ָ
GLUquadricObj *gluQua   ;             //���ڴ洢�����������
GLuint gluTexture[10]    ;            //���ڴ�������
GLdouble dFar = 1E10    ;             //�趨�Ӿ������Զֵ
GLdouble dNear = 5   ;             //�趨�Ӿ�������ֵ
WORLD WorldInfo         ;             //���ֲ���
TCHAR szAppName[] = TEXT("MENU1");


/////////////////////////////////////////////////////////////////////////////////////////////

void DrawGLScene(void)//��ͼ����
{
    Planet *Info = PlanetInfo ;                                //����һ�� Info ָ�����ں������������ı� PlanetInfo ����Ϣ
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;      //�����Ļ����Ȼ���

    Whirl( &gldXrot, &gldYrot, &gldDeep, Info, iPlanetNumber, dNear, dFar) ;//�����ӽ�

    if(bDrawCs)                                                //���� bDrawCs ��ֵ�����Ƿ��������ϵ
    {
        DrawCS(WorldInfo.Multiply);                            //�������������ģ�����һ��ֱ������ϵ
    }

    if(!bMod)                                                  //���� bMod ��ֵ�����Ƿ����Ĭ�� demo
    {                                                          //��ʱ���ƴ��ļ��ж������������
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)             //��������
        {
            DrawPlanet(Info);                                  //��������
            Info = Info->next ;                                //�л�����һ������
        }
    }
    else
    {                                                          //��ʱ����Ĭ�ϵ� demo
        DrawSun( Info, gluQua, &gluTexture[0], bPause) ;       //����̫��

        GLfloat lPos[]= { Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0], 1 } ;// ��Դλ�� ʼ����̫������
        GLfloat lDif[]= { 1, 1, 1, 1} ;  				                                //��������
        GLfloat lamb[] = { 1, 1, 1, 1} ;                                                //ȫ�ֻ���������
        glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lamb) ;   //����ȫ�ֻ�����
        glLightfv( GL_LIGHT0, GL_DIFFUSE, lDif) ;         //���û�����
        glLightfv( GL_LIGHT0, GL_POSITION, lPos) ;        //���ù�Դλ��
        glEnable(GL_LIGHT0);                              //���� 0 �Ź�Դ

        Info = Info->next ;                                 //�л�����һ������
        glEnable(GL_LIGHTING);                              //������Դ
        DrawMercury( Info, gluQua, &gluTexture[1], bPause) ;//����ˮ��
        Info = Info->next ;                                 //�л�����һ������
        DrawVenus( Info, gluQua, &gluTexture[2], bPause) ;  //���ƽ���
        Info = Info->next ;                                 //�л�����һ������
        DrawEarth( Info, gluQua, &gluTexture[3], bPause) ;  //���Ƶ���
        Info = Info->next ;                                 //�л�����һ������
        DrawMars( Info, gluQua, &gluTexture[4], bPause) ;   //���ƻ���
        Info = Info->next ;                                 //�л�����һ������
        DrawJupiter( Info, gluQua, &gluTexture[5], bPause) ;//����ľ��
        Info = Info->next ;                                 //�л�����һ������
        DrawSaturn( Info, gluQua, &gluTexture[6], bPause) ; //��������
        Info = Info->next ;                                 //�л�����һ������
        DrawUranus( Info, gluQua, &gluTexture[7], bPause) ; //��������
        Info = Info->next ;                                 //�л�����һ������
        DrawNeptune( Info, gluQua, &gluTexture[8], bPause) ;//���ƺ���
        Info = Info->next ;                                 //�л�����һ������
        DrawMoon( Info, gluQua, &gluTexture[9], bPause) ;   //��������
        glDisable(GL_LIGHTING);                             //�رչ�Դ

        Info = Info->next ;                               //�л�����һ������

    }

    if(bDrawOrbit)                                        //���� bDrawOrbit ��ֵ�����Ƿ���ƹ켣
    {
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)
        {
            DrawOrbit( Info, WorldInfo.Orbit) ;           //�������ǹ켣
            Info = Info->next ;
        }
    }

    if(!bPause)                                           //���� bPause �ж��Ƿ�����ͣ״̬
    {                                                     //���û�д�����ͣ״̬
        for(int i = 0; i<WorldInfo.PlanetQty; ++i)
        {
            Info->orbit = Info->orbit->next ;             //����ǰ�켣������ƶ�
            SaveOrbit(Info);                              //������״̬������켣����
            Info = Info->next ;                           //�л�����һ������
        }
    }

    SwapBuffers(hDC);                                     //����˫�ػ�����


}


LRESULT CALLBACK ScreenWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//��ʾ���ڹ��̺���
{
    static POINT mousepoint_pt[2] ;//���ڴ洢��ǰ���λ�����ϴ����λ�ã���һ�������洢��һ�ε����λ�ã��ڶ����洢��ǰ���λ��

    static HINSTANCE hInstance;

	switch (msg)//��Ϣ����
	{
        case WM_CREATE://�����ڴ���ʱ
            {
                SetTimer( hwnd, 1, 40, NULL) ;

                WorldInfo = GetPlaNum(sPlaInfoFileName) ;//���ļ��л�ȡ��ʼ��Ϣ

                if(WorldInfo.PlanetQty > 0)//���������ļ���ȡ��Ϣʱ
                {
                    bMod = FALSE ;//����� demo ģʽ
                    gldDeep = -5*WorldInfo.Multiply ;
                    PlanetInfo = CreateInfoLs( WorldInfo.PlanetQty, WorldInfo.Orbit) ;//��������������������ȵ�����
                    GetPlaInfo( PlanetInfo, sPlaInfoFileName, WorldInfo.PlanetQty) ;  //���ļ��ж�ȡ�����ǵ���Ϣ
                    SetZero( PlanetInfo, WorldInfo.PlanetQty, WorldInfo.Orbit) ;      //�Թ켣������г�ʼ��
                }
                else
                {
                    bMod = TRUE ;                                                     //���� demo ģʽ
                    iPlanetNumber = -1 ;                                              //�趨�۲�����Ϊָ�����
                    gldDeep = -3000 ;                                                 //�趨�ӽ����
                    gldXrot = 0, gldYrot = -180 ;                                     //x y����ת�ĽǶ�
                    SetDefaultWorld(&WorldInfo);                                      //�趨Ĭ�ϵ�������ֵ
                    PlanetInfo = CreateInfoLs( WorldInfo.PlanetQty, WorldInfo.Orbit) ;//��������������������ȵ�����
                    SetDefaultInfo(PlanetInfo);                                       //�趨Ĭ��ֵ
                    SetZero( PlanetInfo, WorldInfo.PlanetQty, WorldInfo.Orbit) ;      //�Թ켣������г�ʼ��
                }
                _beginthread( Draw, 0, NULL) ;                                        //������ͼ�߳�
                _beginthread( Computer, 0, NULL) ;                                    //���������߳�

                hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
                return 0 ;
            }

        case WM_TIMER:
            {

                return 0 ;
            }

        case WM_MOUSEWHEEL://������������Ϣ
            {
                switch(HIWORD(wParam))
                {
                    case 120: gldDeep -= 0.5*gldDeep ;break;
                    case 65416: gldDeep += 0.5*gldDeep ;break;
                }
                return 0 ;
            }

        case WM_LBUTTONDOWN://���Ҽ�����ʱ
            {
                //��ȡ���ĵ�ǰλ��
                mousepoint_pt[0].x = LOWORD(lParam) ;
                mousepoint_pt[0].y = HIWORD(lParam) ;

                return 0 ;
            }

        case WM_MOUSEMOVE://����ƶ�ʱ
            {
                if(wParam&MK_LBUTTON)  //������ƶ�ʱ�Ҽ�����
                {
                    //��ȡ��ǰ���λ��
                    mousepoint_pt[1].x = LOWORD(lParam) ;
                    mousepoint_pt[1].y = HIWORD(lParam) ;

                    //�����ӽ���ת�ĽǶ�
                    gldYrot -= 0.5*(mousepoint_pt[0].x - mousepoint_pt[1].x) ;
                    gldXrot += 0.5*(mousepoint_pt[1].y - mousepoint_pt[0].y) ;

                    //������ϣ����ɵ����λ�øı�Ϊ��ǰ���λ�ã��Խ��к�������
                    mousepoint_pt[0].x = mousepoint_pt[1].x ;
                    mousepoint_pt[0].y = mousepoint_pt[1].y ;
                }

                return 0 ;
            }

        case WM_KEYDOWN://�а�������
            {
                switch(wParam)
                {
                    case VK_SPACE://���ո񱻰���ʱ
                        {
                            bPause = !bPause ;//��ת��ͣ״̬
                            break;
                        }

                    case VK_B://�� B ������ʱ
                        {
                            bDrawOrbit = !bDrawOrbit ;//��ת���ƹ켣��״̬
                            break;
                        }

                    case VK_C://��C������ʱ
                        {
                            bDrawCs = !bDrawCs ;//��ת��������ϵ��״̬
                            break;
                        }

                    case VK_Q://��Q������ʱ
                        {
                            iPlanetNumber += 1 ;
                            if(iPlanetNumber==WorldInfo.PlanetQty)//����ǰ�������ĵ����Ǳ�ų����������Ǳ��
                            {
                                iPlanetNumber = -1 ;//ʹ��ǰ�۲����Ǳ����Ϊ����ϵ����
                            }
                            break;
                        }

                    case VK_E://��E������ʱ
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

        case WM_SIZE://���ڴ�С�����仯
            {
                SendMessage( hDrawWindow, WM_SIZE, wParam, lParam) ;//���µĳߴ紫�ݸ���ͼ���ڹ��̣��Խ����ӿڵ�����
                return 0 ;
            }

        case WM_CLOSE://�յ��رմ�����Ϣ
            {
                SendMessage( hDrawWindow, WM_CLOSE, 0, 0) ;    //����WM_CLOSE����ͼ���ڹ��̣��������Ӧ��Դ
                return 0 ;
            }

        case WM_DESTROY://���ٴ���
            {
                PostQuitMessage(0);
                return 0 ;
            }

        case WM_COMMAND:
		switch (LOWORD(wParam))
		{
                case ID_SP:
                        {
                            bPause = !bPause ;//��ת��ͣ״̬
                            break;
                        }


		case ID_Exit:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;

                case ID_ShowHideC:
                        {
                            bDrawCs = !bDrawCs ;//��ת��������ϵ��״̬
                            break;
                        }

                case ID_ShowHideB:
                        {
                            bDrawOrbit = !bDrawOrbit ;//��ת���ƹ켣��״̬
                            break;
                        }

                case ID_ChangeQ:
                         {
                            iPlanetNumber += 1 ;
                            if(iPlanetNumber==WorldInfo.PlanetQty)//����ǰ�������ĵ����Ǳ�ų����������Ǳ��
                            {
                                iPlanetNumber = -1 ;//ʹ��ǰ�۲����Ǳ����Ϊ����ϵ����
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

	return DefWindowProc( hwnd, msg, wParam, lParam) ;// ��DefWindowProc����δ�������Ϣ
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message,WPARAM wParam, LPARAM lParam) //�Ի������
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





int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)//�������
{
	MSG		   msg ;// ������Ϣ�ṹ��
    WNDCLASS	wc ;// ������ṹ��

	wc.style		 = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;	             //��С�ı�ʱ�ػ����ڣ�Ϊ����ȡ��DC
	wc.lpfnWndProc	 = (WNDPROC)ScreenWindow ;				             //ָ�����ڹ��̺���
	wc.cbClsExtra	 = 0 ;
	wc.cbWndExtra	 = 0 ;
	wc.hInstance   	 = hInstance ;                                       //����ʵ������
	wc.hIcon		 = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1)) ;//����ͼ��
	wc.hCursor		 = LoadCursor( NULL, IDC_ARROW) ;                    //����Ĭ�����ͼ��
	wc.hbrBackground = NULL ;                                            //���ڱ���ɫ
	wc.lpszMenuName	 = szAppName ;                                            //�޲˵�
	wc.lpszClassName = "OpenGlScreen" ;						             //�趨��������

	if (!RegisterClass(&wc))									         //ע�ᴰ����
	{
	    ErrorBox("Failed to register the screen window class.");
		return 0 ;//���ע�ᴰ����ʧ�����˳�
	}

	if (!CreateGLWindow( "OpenGlScreen", sAppName, iWidth, iHeight, &hScreenWindow))//����OpenGl����
	{
	    ErrorBox("Failed to create screen window");
		return 0 ;//�����ڴ���ʧ�����˳�
	}

    while (GetMessage ( &msg, NULL, 0, 0))//������Ϣѭ��
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

	return (msg.wParam) ;				  //�˳�����
}


void Draw(PVOID pVoid)//��ͼ�̺߳���
{
    MSG         msg ; //������Ϣ�ṹ��
    WNDCLASS     wc ; //������ṹ��

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //��С�ı�ʱ�ػ�����
	wc.lpfnWndProc		= (WNDPROC)DrawWindow ;					//ָ�����ڹ��̺���
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //����ʵ������
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //����ͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //�������ͼ��
	wc.hbrBackground	= NULL ;                                //���ڱ���ɫ
	wc.lpszMenuName		= NULL ;                                //�޲˵�
	wc.lpszClassName	= "OpenGlDraw" ;						//��������

	if (!RegisterClass(&wc))									//ע�ᴰ����
	{
	    ErrorBox("Failed to register draw window class");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //������ע��ʧ�����˳�����
	}


    hDrawWindow = CreateWindowEx( 0,                            //������ͼ�߳����õĴ���
                                 "OpenGlDraw", "Draw",
                                 WS_POPUP, 0, 0, 0, 0,
                                 NULL, NULL,
                                 GetModuleHandle(NULL),
                                 NULL
                                 ) ;
    if(hDrawWindow==NULL)
    {
        ErrorBox("Failed to create draw window");
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //��������ʧ�����˳�����
    }

    GlRelateWindow( &hScreenWindow, &hDC, &hRC) ;               //����ʾ������OpenGl�����
    ReSizeGLScene( 0, 0, iWidth, iHeight, dNear, dFar) ;	    //����͸��GL��Ļ

    if(bMod)                                                    //�����ǰ���� demo ģʽ ����������
    {
        LoadGLTextures( &gluTexture[0], "data\\sun.bmp") ;      //����̫������
        LoadGLTextures( &gluTexture[1], "data\\Mercury.bmp") ;  //����ˮ������
        LoadGLTextures( &gluTexture[2], "data\\Venus.bmp") ;    //�����������
        LoadGLTextures( &gluTexture[3], "data\\earth.bmp") ;    //�����������
        LoadGLTextures( &gluTexture[4], "data\\Mars.bmp") ;     //�����������
        LoadGLTextures( &gluTexture[5], "data\\Jupiter.bmp") ;  //����ľ������
        LoadGLTextures( &gluTexture[6], "data\\Saturn.bmp") ;   //������������
        LoadGLTextures( &gluTexture[7], "data\\Uranus.bmp") ;   //������������
        LoadGLTextures( &gluTexture[8], "data\\Neptune.bmp") ;  //���뺣������
        LoadGLTextures( &gluTexture[9], "data\\moon.bmp") ;     //������������

    }

    gluQua = InitGL();                                          //��ʼ���½���GL����

    //�����빤����ɺ󼤻� screen ����
    SetForegroundWindow(hScreenWindow);                         //���� Screen ����
    SetFocus(hScreenWindow);                                    //�����̽������õ� Screen ����

    while (GetMessage ( &msg, NULL, 0, 0))                      //������Ϣѭ��
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

}


LRESULT CALLBACK DrawWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//��ͼ�̴߳��ڹ��̺���
{

    switch(msg)  //��Ϣ����
    {
        case WM_CREATE://���ڴ���ʱ
            {
                SetTimer( hwnd, 1, 40, NULL) ;//�趨һ��ʱ��
                return 0 ;
            }

        case WM_SAVEBMP:
            {
                SaveBmp( 0, 0, iHeight, iWidth) ;//�����ڴ�С�����ͼ����
                return 0 ;
            }

        case WM_TIMER://�յ�ʱ�ӷ�������Ϣ
            {
                DrawGLScene();   //���л�ͼ
                return 0 ;
            }

        case WM_SIZE://�յ�������ʾ���ڵĴ�С�ı����Ϣ
            {
                iWidth = LOWORD(lParam) ;
                iHeight = HIWORD(lParam) ;
                ReSizeGLScene( 0, 0, iWidth, iHeight, dNear, dFar) ;//����ʾ���ڴ�С�仯ʱ������OpenGl�ӿ�
                return 0 ;
            }

        case WM_CLOSE://�յ��رմ�����Ϣ
            {
                KillGLWindow( &hDrawWindow, &hDC, &hRC) ;//����DC RC
                SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;
                return 0 ;
            }
    }
    return DefWindowProc(hwnd,msg,wParam,lParam) ;//��DefWindowProc����δ�������Ϣ
}


void Computer(PVOID void_pv)//�����̺߳���
{
    MSG         msg ; //������Ϣ�ṹ��
    WNDCLASS     wc ; //������ṹ��

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //��С�ı�ʱ�ػ�����
	wc.lpfnWndProc		= (WNDPROC)ComputerWindow ;				//ָ�����ڹ��̺���
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //����ʵ������
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //����ͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //�������ͼ��
	wc.hbrBackground	= NULL ;                                //���ڱ���ɫ
	wc.lpszMenuName		= NULL ;                                //�޲˵�
	wc.lpszClassName	= "OpenGlComputer" ;					//��������


	if (!RegisterClass(&wc))									//ע�ᴰ����
	{
	    ErrorBox("Failed to register computer window class.");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //ע�ᴰ����ʧ�����˳�����
	}

    hComputerWindow = CreateWindowEx( 0,                        //�������õĴ���
                                      "OpenGlComputer", "Computer",
                                      WS_POPUP, 0, 0, 0, 0,
                                      NULL, NULL,
                                      GetModuleHandle(NULL),
                                      NULL
                                    ) ;

	if(hComputerWindow==NULL)
    {
        ErrorBox("Failed to create computer window.");
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //��������ʧ�����˳�����
    }


    while (GetMessage ( &msg, NULL, 0, 0))                      //������Ϣѭ��
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }


}


LRESULT CALLBACK ComputerWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//�����̴߳��ڹ��̺���
{
    switch(msg)  //��Ϣ����
    {
        case WM_CREATE:
            {
                SetTimer( hwnd, 1, 40, NULL) ;//����һ��ʱ����ȷ������Ƶ��
                return 0 ;
            }

        case WM_TIMER://�յ�ʱ�ӷ�������Ϣ
            {
                //time_t start = time(NULL) ;

                for(int i=0; i<WorldInfo.CalRate; i++)//���� iCalRate �μ���
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
    return DefWindowProc(hwnd,msg,wParam,lParam) ;//��DefWindowProc����δ�������Ϣ

}


void InfoBar(PVOID pVoid)
{
    MSG         msg ; //������Ϣ�ṹ��
    WNDCLASS     wc ; //������ṹ��

	wc.style			= CS_HREDRAW | CS_VREDRAW ;	            //��С�ı�ʱ�ػ�����
	wc.lpfnWndProc		= (WNDPROC)InfoBarWindow ;				//ָ�����ڹ��̺���
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle(NULL) ;               //����ʵ������
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO) ;         //����ͼ��
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW) ;         //�������ͼ��
	wc.hbrBackground	= NULL ;                                //���ڱ���ɫ
	wc.lpszMenuName		= NULL ;                                //�޲˵�
	wc.lpszClassName	= "InfoBar" ;					        //��������

	if (!RegisterClass(&wc))									//ע�ᴰ����
	{
	    ErrorBox("Failed to register InfoBar window class.");
		SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //ע�ᴰ����ʧ�����˳�����
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
        SendMessage( hScreenWindow, WM_DESTROY, 0, 0) ;         //��������ʧ�����˳�����
    }



    while (GetMessage ( &msg, NULL, 0, 0))                      //������Ϣѭ��
    {
        TranslateMessage (&msg) ;
        DispatchMessage (&msg) ;
    }

}



LRESULT CALLBACK InfoBarWindow( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)//��Ϣ���̴߳��ڹ��̺���
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

















