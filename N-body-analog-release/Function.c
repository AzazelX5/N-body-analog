#include "Fun.h"



void Calculate( Planet *Info, int iQty, long double h, double G)//经典龙格库塔法实现计算
{
    Planet *p1, *p2 ;
    p1 = p2 = Info ;
	long double R, r, a, Vx, Vy, Vz ;
	long double x0, y0, z0 ;
	int i, j, k ;

	for (i = 0; i < iQty; ++i)
	{
	    for(j = 0; j < 4; ++j)
        {
            for(k = 0; k < 3; ++k)
            {
                p1->k[j][k] = 0 ;
            }
        }
        p1 = p1->next ;
	}


	for (i = 0; i < iQty; ++i)//求出K1
	{
		for (j = 0; j < iQty; ++j)
		{
			if ( i<j )
			{
				x0 = p2->x[0] - p1->x[0] ;
				y0 = p2->y[0] - p1->y[0] ;
			    z0 = p2->z[0] - p1->z[0] ;
			    R = x0*x0 + y0*y0 + z0*z0 ;
			    r = sqrt(R) ;
			    a = G*p2->m/R ;

			    p1->k[0][0] += a*x0/r ;
			    p1->k[0][1] += a*y0/r ;
			    p1->k[0][2] += a*z0/r ;

			    a = G*p1->m/R ;

			    p2->k[0][0] -= a*x0/r ;
			    p2->k[0][1] -= a*y0/r ;
			    p2->k[0][2] -= a*z0/r ;
			}
			p2 = p2->next ;
		}
		p1 = p1->next ;
	}


	for (i = 0; i < iQty; ++i)//根据 k1 算出 n+1/2 时的数据
	{
	    Vx = p1->V[0] + 0.5*h*p1->k[0][0] ;
	    p1->x[1] = p1->x[0] + 0.5*p1->V[0]*h + 0.25*p1->k[0][0]*h*h ;

	    Vy = p1->V[1] + 0.5*h*p1->k[0][1] ;
	    p1->y[1] = p1->y[0] + 0.5*p1->V[1]*h + 0.25*p1->k[0][1]*h*h ;

	    Vz = p1->V[2] + 0.5*h*p1->k[0][2] ;
	    p1->z[1] = p1->z[0] + 0.5*p1->V[2]*h + 0.25*p1->k[0][2]*h*h ;

	    p1 = p1->next ;
	}


	for (i = 0; i < iQty; ++i)//求出K2
	{
		for (j = 0; j < iQty; ++j)
		{
			if ( i<j )
			{
				x0 = p2->x[1] - p1->x[1] ;
				y0 = p2->y[1] - p1->y[1] ;
			    z0 = p2->z[1] - p1->z[1] ;
			    R = x0*x0 + y0*y0 + z0*z0 ;
			    r = sqrt(R) ;
			    a = G*p2->m/R ;

			    p1->k[1][0] += a*x0/r ;
			    p1->k[1][1] += a*y0/r ;
			    p1->k[1][2] += a*z0/r ;

			    a = G*p1->m/R ;

			    p2->k[1][0] -= a*x0/r ;
			    p2->k[1][1] -= a*y0/r ;
			    p2->k[1][2] -= a*z0/r ;
			}
			p2 = p2->next ;
		}
		p1 = p1->next ;
	}



	for (i = 0; i < iQty; ++i)//根据 k2 算出 n+1/2 时的数据
	{
	    Vx = p1->V[0] + 0.5*h*p1->k[1][0] ;
	    p1->x[1] = p1->x[0] + 0.5*p1->V[0]*h + 0.25*p1->k[1][0]*h*h ;

	    Vy = p1->V[1] + 0.5*h*p1->k[1][1] ;
	    p1->y[1] = p1->y[0] + 0.5*p1->V[1]*h + 0.25*p1->k[1][1]*h*h ;

	    Vz = p1->V[2] + 0.5*h*p1->k[1][2] ;
	    p1->z[1] = p1->z[0] + 0.5*p1->V[2]*h + 0.25*p1->k[1][2]*h*h ;

	    p1 = p1->next ;
	}



	for (i = 0; i < iQty; ++i)//求出K3
	{
		for (j = 0; j < iQty; ++j)
		{
			if ( i<j )
			{
				x0 = p2->x[1] - p1->x[1] ;
				y0 = p2->y[1] - p1->y[1] ;
			    z0 = p2->z[1] - p1->z[1] ;
			    R = x0*x0 + y0*y0 + z0*z0 ;
			    r = sqrt(R) ;
			    a = G*p2->m/R ;

			    p1->k[2][0] += a*x0/r ;
			    p1->k[2][1] += a*y0/r ;
			    p1->k[2][2] += a*z0/r ;

			    a = G*p1->m/R ;

			    p2->k[2][0] -= a*x0/r ;
			    p2->k[2][1] -= a*y0/r ;
			    p2->k[2][2] -= a*z0/r ;
			}
			p2 = p2->next ;
		}
		p1 = p1->next ;
	}



	for (i = 0; i < iQty; ++i)//根据 k3 算出 n+1 时的数据
	{
	    Vx = p1->V[0] + h*p1->k[2][0] ;
	    p1->x[1] = p1->x[0] + p1->V[0]*h + 0.5*p1->k[2][0]*h*h ;

	    Vy = p1->V[1] + h*p1->k[2][1] ;
	    p1->y[1] = p1->y[0] + p1->V[1]*h + 0.5*p1->k[2][1]*h*h ;

	    Vz = p1->V[2] + h*p1->k[2][2] ;
	    p1->z[1] = p1->z[0] + p1->V[2]*h + 0.5*p1->k[2][2]*h*h ;

	    p1 = p1->next ;
	}



    for (i = 0; i < iQty; ++i)//求出K4
	{
		for (j = 0; j < iQty; ++j)
		{
			if ( i<j )
			{
				x0 = p2->x[1] - p1->x[1] ;
				y0 = p2->y[1] - p1->y[1] ;
			    z0 = p2->z[1] - p1->z[1] ;
			    R = x0*x0 + y0*y0 + z0*z0 ;
			    r = sqrt(R) ;
			    a = G*p2->m/R ;

			    p1->k[3][0] += a*x0/r ;
			    p1->k[3][1] += a*y0/r ;
			    p1->k[3][2] += a*z0/r ;

			    a = G*p1->m/R ;

			    p2->k[3][0] -= a*x0/r ;
			    p2->k[3][1] -= a*y0/r ;
			    p2->k[3][2] -= a*z0/r ;
			}
			p2 = p2->next ;
		}
		p1 = p1->next ;
	}



    for(i = 0; i < iQty; ++i)
    {
        Vx = p1->V[0] + h/6*(p1->k[0][0] + 2*p1->k[1][0] + 2*p1->k[2][0] + p1->k[3][0]) ;
        p1->x[0] += 0.5*h*(Vx + p1->V[0]) ;
        p1->V[0] = Vx ;

        Vy = p1->V[1] + h/6*(p1->k[0][1] + 2*p1->k[1][1] + 2*p1->k[2][1] + p1->k[3][1]) ;
        p1->y[0] += 0.5*h*(Vy + p1->V[1]) ;
        p1->V[1] = Vy ;

        Vz = p1->V[2] + h/6*(p1->k[0][2] + 2*p1->k[1][2] + 2*p1->k[2][2] + p1->k[3][2]) ;
        p1->z[0] += 0.5*h*(Vz + p1->V[2]) ;
        p1->V[2] = Vz ;

        p1 = p1->next ;
    }



}


Planet *CreateInfoLs(int num, int OrbitNum)//创建长度为i的双向环形链表
{
    Planet *head = (Planet *)malloc(sizeof(Planet)) ;
    Planet *now, *New, *nowOrbit, *NewOrbit ;

    head->orbit = (Planet *)malloc(sizeof(Planet)) ;//创建一个新的轨迹节点
    nowOrbit = head->orbit ;                        //使头轨迹节点成为当前轨迹节点

    for(int i = 1; i<OrbitNum; ++i)
    {
        NewOrbit = (Planet *)malloc(sizeof(Planet)) ;//创建一个新的轨迹节点

        nowOrbit->next = NewOrbit ;                  //当前轨迹节点的 next 指向新轨迹节点
        NewOrbit->previous = nowOrbit ;              //新轨迹节点的 previous 指向当前轨迹节点

        nowOrbit = NewOrbit ;                        //新轨迹节点成为当前轨迹节点
    }
    nowOrbit->next = head->orbit ;                   //当前轨迹节点的 next 指向轨迹头节点
    head->orbit->previous = nowOrbit ;               //头轨迹节点的 previous 指向当前轨迹节点  最终使链表成为环形

    now = head ;                                     //使头节点成为当前节点
    for(int i = 1; i<num; ++i)
    {
        New = (Planet *)malloc(sizeof(Planet)) ;     //创建一个新节点

                New->orbit = (Planet *)malloc(sizeof(Planet)) ;  //创建一个新的轨迹节点
                nowOrbit = New->orbit ;              //使头轨迹节点成为当前轨迹节点
                for(int j = 1; j<OrbitNum; ++j)
                {
                    NewOrbit = (Planet *)malloc(sizeof(Planet)) ;//创建一个新的轨迹节点

                    nowOrbit->next = NewOrbit ;      //当前轨迹节点的 next 指向新轨迹节点
                    NewOrbit->previous = nowOrbit ;  //新轨迹节点的 previous 指向当前轨迹节点

                    nowOrbit = NewOrbit ;            //新轨迹节点成为当前轨迹节点
                }
                nowOrbit->next = New->orbit ;        //当前轨迹节点的 next 指向轨迹头节点
                New->orbit->previous = nowOrbit ;    //头轨迹节点的 previous 指向当前轨迹节点  最终使链表成为环形

        now->next = New ;                            //当前节点的 next 指向新节点
        New->previous = now ;                        //新节点的 previous 指向当前节点

        now = New ;                                  //新节点成为当前节点

    }                                                //节点创建完毕

    now->next = head ;                               //当前节点的 next 指向头节点
    head->previous = now ;                           //头节点的 previous 指向当前节点   最终使链表成为环形

    return head ;                                    //返回指向头节点的指针

}


void SaveOrbit(Planet *Info)//保存轨迹点
{
    Info->orbit->r = Info->r ;
    Info->orbit->x[0] = Info->x[0] ;
    Info->orbit->y[0] = Info->y[0] ;
    Info->orbit->z[0] = Info->z[0] ;
}


void SetZero(Planet *Info, int num, int OrbitNum)//对轨迹链表进行初始化
{
    for(int i = 0; i<num; ++i)
    {
        for(int j = 0; j<OrbitNum; ++j)
        {
            Info->orbit->r = Info->r ;
            Info->orbit->x[0] = Info->x[0] ;
            Info->orbit->y[0] = Info->y[0] ;
            Info->orbit->z[0] = Info->z[0] ;
            Info->orbit = Info->orbit->next ;
        }
        Info = Info->next ;
    }
}


WORLD GetPlaNum(char sInfoFileName[])//从文件中获取初始信息
{
    FILE *fp ;
    WORLD world ;
    fp = fopen( sInfoFileName, "r") ;     //打开文件
    if(fp==NULL)
    {
        ErrorBox("Can not find info.dat");//若文件打开失败报错
        world.PlanetQty = 0 ;
        return world ;
    }

    fscanf( fp, "%d", &world.Multiply) ;  //获取坐标轴单位长度
    fscanf( fp, "%d", &world.Orbit) ;     //读取轨迹的长度
    fscanf( fp, "%d", &world.PlanetQty) ; //获取行星的数量
    fscanf( fp, "%le", &world.CalRate) ;  //获取计算频率
    fscanf( fp, "%le", &world.G) ;        //获得万有引力常量
    fscanf( fp, "%le", &world.StepSize) ; //获取计算步长

    fclose( fp) ;                         //关闭文件

    return world ;                        //返回所读到的信息
}


int GetPlaInfo(Planet *Info, char sInfoFileName[], int num)//从文件中获取行星数据，并存入链表中
{
    double x, y, z, Vx, Vy, Vz, r, m ;//用于存储从文件中读出的数据
    FILE *fp ;
    WORLD world ;
    fp = fopen( sInfoFileName, "r") ;//打开文件
    if(fp==NULL)
    {
        ErrorBox("GetPlaInfo Error");//若文件打开失败报错
        return 0 ;
    }

    fscanf( fp, "%d", &world.Multiply) ;  //获取坐标轴单位长度
    fscanf( fp, "%d", &world.Orbit) ;     //读取轨迹的长度
    fscanf( fp, "%d", &world.PlanetQty) ; //获取行星的数量
    fscanf( fp, "%le", &world.CalRate) ;  //获取计算频率
    fscanf( fp, "%le", &world.G) ;        //获得万有引力常量
    fscanf( fp, "%le", &world.StepSize) ; //获取计算步长

    for(int i = 0; i<num; ++i)
    {
        fscanf( fp, "%lf%lf%lf%lf%lf%lf%lf%lf",
               &r, &m, &Vx, &Vy, &Vz, &x, &y, &z) ;//将数据每8个一组读出
        Info->r = (long double)r, Info->m = (long double)m ;
        Info->V[0] = (long double)Vx, Info->V[1] = (long double)Vy,  Info->V[2] = (long double)Vz ;
        Info->x[0] = (long double)x, Info->y[0] = (long double)y, Info->z[0] = (long double)z ;//将读到的数据存入链表节点中
        Info = Info->next ;//节点向下移动一位
    }

    return 1 ;
}


void SetDefaultInfo(Planet *Info)//当不存在 info.dat 文件时 使用此函数设定默认数值 近似日地月稳定系统
{
    double i = 1 ;
    double l = 0;
    Info->r = l+i*695.55, Info->m = 1989000 ;
    Info->V[0] = 0, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 0 ;              //太阳数据
    Info = Info->next ;

    Info->r = l+i*2.44, Info->m = 0.3302 ;
    Info->V[0] = 0.05896, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 46001.2 ;        //水星数据
    Info = Info->next ;

    Info->r = l+i*2.44, Info->m = 4.869 ;
    Info->V[0] = 0.035258, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 107476.259 ;     //金星数据
    Info = Info->next ;

    Info->r = l+i*6.378, Info->m = 6 ;
    Info->V[0] = 0.029, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 152097.7 ;       //地球数据
    Info = Info->next ;

    Info->r = l+i*6.7, Info->m = 0.64219 ;
    Info->V[0] = 0.026499, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 206644.545 ;     //火星数据
    Info = Info->next ;

    Info->r = l+i*71.4935, Info->m = 1900 ;
    Info->V[0] = 0.013719, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 740520 ;         //木星数据
    Info = Info->next ;

    Info->r = l+i*60.268, Info->m = 569 ;
    Info->V[0] = 0.010175, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 1353572.956 ;    //土星数据
    Info = Info->next ;

    Info->r = l+i*52, Info->m = 86.81 ;
    Info->V[0] = 0.0071, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 2748938.461 ;    //天王数据
    Info = Info->next ;

    Info->r = l+i*24.766, Info->m = 102.47 ;
    Info->V[0] = 0.0054899, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 4452940.833 ;    //海王数据
    Info = Info->next ;

    Info->r = l+i*1.737, Info->m = 0.07349 ;
    Info->V[0] = 0.03, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 384.4, Info->z[0] = 152097.7 ;   //月球数据

    Info = Info->next ;

}


void SetDefaultWorld(WORLD *WorldInfo)
{
    WorldInfo->PlanetQty = 10 ;     //设定行星数量
    WorldInfo->Multiply = 150000 ; //设定坐标系单位长度
    WorldInfo->Orbit = 100000 ;  //设定轨迹点长度
    WorldInfo->CalRate = 1E5 ;     //设定计算步长
    WorldInfo->StepSize = 2 ;      //设定时间步长为 1s
    WorldInfo->G = 6.67E-5 ;       //设定万有引力常量


}


AUX_RGBImageRec *LoadBMP(char *Filename)// 载入位图图象
{
	FILE *File=NULL;	// 文件句柄
	if (!Filename)		// 确保文件名已提供
	{
		return NULL;	// 如果没提供，返回 NULL
	}
	File=fopen( Filename,"r");	// 尝试打开文件
	if (File)					// 如果文件存在
	{
		fclose(File);						// 关闭句柄
		return auxDIBImageLoad(Filename);	// 载入位图并返回指针
	}
	return NULL;							// 如果载入失败，返回 NULL
}


int LoadGLTextures(GLuint *texture, char *Filename)// 载入位图并转换成纹理
{
    if (!Filename)	//确保文件名已提供
	{
		return 0 ;	//如果没提供，返回 0
	}
	AUX_RGBImageRec *TextureImage[1] ;            //创建纹理的存储空间
	memset(TextureImage,0,sizeof(void *)*1);
	TextureImage[0] = LoadBMP(Filename) ;         //载入位图

    if(!TextureImage[0])
    {
        *texture = 0 ;
        _beginthread( ErrorMsg, 0, Filename) ;    //创建报错线程
        return 0 ;
    }

	if(TextureImage)
    {
        glGenTextures( 1, texture) ;                                    //创建纹理
        glBindTexture(GL_TEXTURE_2D, *texture);

        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//线形滤波
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	//线形滤波


        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
    }
    else
    {
        return 0 ;
    }

    free(TextureImage[0]->data) ;//释放纹理图像占用的内存
    free(TextureImage[0]);       // 释放图像结构

	return 1 ;
}







/*
GLuint *LoadGLTextures(void)//从资源文件读入图像并转化为纹理
{

	HBITMAP hBMP;//位图句柄
	BITMAP	BMP; //位图结构


    glGenTextures( 3, &gluTexture[0]);//创建3个纹理
    //hBMP = LoadBitmap ( GetModuleHandle(NULL), MAKEINTRESOURCE (IDB_BITMAP1) );
    hBMP = (HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//当位图成功载入时
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//获取位图
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//以四字节方式对其内存
        glBindTexture( GL_TEXTURE_2D, gluTexture[0]) ;//绑定位图
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//线形滤波
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//线性滤波

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//创建纹理
        DeleteObject(hBMP);	//删除位图对象
    }
    else
    {
        MessageBox( NULL, "ERROR", "ERROR", MB_OK) ;
    }

    hBMP=(HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//当位图成功载入时
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//获取位图
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//以四字节方式对其内存
        glBindTexture( GL_TEXTURE_2D, gluTexture[1]) ;//绑定位图
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//线形滤波
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//线性滤波

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//创建纹理
        DeleteObject(hBMP);	//删除位图对象
    }

    hBMP=(HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//当位图成功载入时
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//获取位图
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//以四字节方式对其内存
        glBindTexture( GL_TEXTURE_2D, gluTexture[2]) ;//绑定位图
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//线形滤波
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//线性滤波

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//创建纹理
        DeleteObject(hBMP);	//删除位图对象
    }
    return NULL ;
}

*/



void SaveBmp( GLint x, GLint y, GLint height, GLint width)
{
    int BmpSize = height*width*3 ;
    int Completion = 4 - width%4 ;            //bmp中宽度必须为4的倍数 这里计算宽度需要增加多少才可成为 4 的倍数
    BmpSize += height*Completion ;            //将每行的宽度进行填充

    BITMAPFILEHEADER BmpHeader = { 0x4D42,    //指明文件类型为 BM
                                   54+BmpSize,//整个BMP文件的大小
                                   0,         //此处必须为0
                                   0,         //此处必须为0
                                   54         //说明从文件头0000h开始到图像像素数据的字节偏移量（以字节Bytes为单位）
                                    } ;

    BITMAPINFOHEADER BmpInfoHeader = { 0x28,  //图像描述信息块的大小，常为28H
                                       width, //图像宽度，以像素为单位
                                       height,//图像高度
                                       1,     //图像的plane总数，恒为1
                                       24,    //记录像素的位数
                                       0,     //数据压缩方式 0为不压缩
                                       0,     //图像区数据的大小。单位字节，该数必须是4的倍数
                                       0,     //水平每米有多少像素，在设备无关位图中，每字节以00H填写
                                       0,     //垂直每米有多少像素，在设备无关位图中，每字节以00H填写
                                       0,     //此图像所用的颜色数
                                       0,     //指定重要的颜色数，当为0时，表示所有颜色一样重要
                                        } ;

    GLubyte *bmp = (GLubyte *)malloc(BmpSize) ;                            //bmp用于存储位图信息
    glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;                               //将帧缓存进行4位对齐
    glReadPixels( x, y, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp) ;//从帧缓存中读出位图



    time_t t ;
    time(&t);//获取当前时间
    struct tm *p ;
    p = localtime(&t) ;//将当前时间转化为本地时间
    char str[50] ;
    sprintf( str, "%d%d%d%d%d%d.bmp", p->tm_year+1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec) ;//将以时间做首的文件名写入字符串
    FILE *fp = fopen( str, "wb") ;
    fwrite( &BmpHeader, sizeof(BmpHeader), 1, fp) ;
    fwrite( &BmpInfoHeader, sizeof(BmpInfoHeader), 1, fp) ;
    fwrite( bmp, BmpSize*sizeof(GLubyte), 1, fp) ;

    fclose(fp);//关闭文件
    free(bmp);//释放内存
}









































































