#include "Fun.h"



void Calculate( Planet *Info, int iQty, long double h, double G)//�������������ʵ�ּ���
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


	for (i = 0; i < iQty; ++i)//���K1
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


	for (i = 0; i < iQty; ++i)//���� k1 ��� n+1/2 ʱ������
	{
	    Vx = p1->V[0] + 0.5*h*p1->k[0][0] ;
	    p1->x[1] = p1->x[0] + 0.5*p1->V[0]*h + 0.25*p1->k[0][0]*h*h ;

	    Vy = p1->V[1] + 0.5*h*p1->k[0][1] ;
	    p1->y[1] = p1->y[0] + 0.5*p1->V[1]*h + 0.25*p1->k[0][1]*h*h ;

	    Vz = p1->V[2] + 0.5*h*p1->k[0][2] ;
	    p1->z[1] = p1->z[0] + 0.5*p1->V[2]*h + 0.25*p1->k[0][2]*h*h ;

	    p1 = p1->next ;
	}


	for (i = 0; i < iQty; ++i)//���K2
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



	for (i = 0; i < iQty; ++i)//���� k2 ��� n+1/2 ʱ������
	{
	    Vx = p1->V[0] + 0.5*h*p1->k[1][0] ;
	    p1->x[1] = p1->x[0] + 0.5*p1->V[0]*h + 0.25*p1->k[1][0]*h*h ;

	    Vy = p1->V[1] + 0.5*h*p1->k[1][1] ;
	    p1->y[1] = p1->y[0] + 0.5*p1->V[1]*h + 0.25*p1->k[1][1]*h*h ;

	    Vz = p1->V[2] + 0.5*h*p1->k[1][2] ;
	    p1->z[1] = p1->z[0] + 0.5*p1->V[2]*h + 0.25*p1->k[1][2]*h*h ;

	    p1 = p1->next ;
	}



	for (i = 0; i < iQty; ++i)//���K3
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



	for (i = 0; i < iQty; ++i)//���� k3 ��� n+1 ʱ������
	{
	    Vx = p1->V[0] + h*p1->k[2][0] ;
	    p1->x[1] = p1->x[0] + p1->V[0]*h + 0.5*p1->k[2][0]*h*h ;

	    Vy = p1->V[1] + h*p1->k[2][1] ;
	    p1->y[1] = p1->y[0] + p1->V[1]*h + 0.5*p1->k[2][1]*h*h ;

	    Vz = p1->V[2] + h*p1->k[2][2] ;
	    p1->z[1] = p1->z[0] + p1->V[2]*h + 0.5*p1->k[2][2]*h*h ;

	    p1 = p1->next ;
	}



    for (i = 0; i < iQty; ++i)//���K4
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


Planet *CreateInfoLs(int num, int OrbitNum)//��������Ϊi��˫��������
{
    Planet *head = (Planet *)malloc(sizeof(Planet)) ;
    Planet *now, *New, *nowOrbit, *NewOrbit ;

    head->orbit = (Planet *)malloc(sizeof(Planet)) ;//����һ���µĹ켣�ڵ�
    nowOrbit = head->orbit ;                        //ʹͷ�켣�ڵ��Ϊ��ǰ�켣�ڵ�

    for(int i = 1; i<OrbitNum; ++i)
    {
        NewOrbit = (Planet *)malloc(sizeof(Planet)) ;//����һ���µĹ켣�ڵ�

        nowOrbit->next = NewOrbit ;                  //��ǰ�켣�ڵ�� next ָ���¹켣�ڵ�
        NewOrbit->previous = nowOrbit ;              //�¹켣�ڵ�� previous ָ��ǰ�켣�ڵ�

        nowOrbit = NewOrbit ;                        //�¹켣�ڵ��Ϊ��ǰ�켣�ڵ�
    }
    nowOrbit->next = head->orbit ;                   //��ǰ�켣�ڵ�� next ָ��켣ͷ�ڵ�
    head->orbit->previous = nowOrbit ;               //ͷ�켣�ڵ�� previous ָ��ǰ�켣�ڵ�  ����ʹ�����Ϊ����

    now = head ;                                     //ʹͷ�ڵ��Ϊ��ǰ�ڵ�
    for(int i = 1; i<num; ++i)
    {
        New = (Planet *)malloc(sizeof(Planet)) ;     //����һ���½ڵ�

                New->orbit = (Planet *)malloc(sizeof(Planet)) ;  //����һ���µĹ켣�ڵ�
                nowOrbit = New->orbit ;              //ʹͷ�켣�ڵ��Ϊ��ǰ�켣�ڵ�
                for(int j = 1; j<OrbitNum; ++j)
                {
                    NewOrbit = (Planet *)malloc(sizeof(Planet)) ;//����һ���µĹ켣�ڵ�

                    nowOrbit->next = NewOrbit ;      //��ǰ�켣�ڵ�� next ָ���¹켣�ڵ�
                    NewOrbit->previous = nowOrbit ;  //�¹켣�ڵ�� previous ָ��ǰ�켣�ڵ�

                    nowOrbit = NewOrbit ;            //�¹켣�ڵ��Ϊ��ǰ�켣�ڵ�
                }
                nowOrbit->next = New->orbit ;        //��ǰ�켣�ڵ�� next ָ��켣ͷ�ڵ�
                New->orbit->previous = nowOrbit ;    //ͷ�켣�ڵ�� previous ָ��ǰ�켣�ڵ�  ����ʹ�����Ϊ����

        now->next = New ;                            //��ǰ�ڵ�� next ָ���½ڵ�
        New->previous = now ;                        //�½ڵ�� previous ָ��ǰ�ڵ�

        now = New ;                                  //�½ڵ��Ϊ��ǰ�ڵ�

    }                                                //�ڵ㴴�����

    now->next = head ;                               //��ǰ�ڵ�� next ָ��ͷ�ڵ�
    head->previous = now ;                           //ͷ�ڵ�� previous ָ��ǰ�ڵ�   ����ʹ�����Ϊ����

    return head ;                                    //����ָ��ͷ�ڵ��ָ��

}


void SaveOrbit(Planet *Info)//����켣��
{
    Info->orbit->r = Info->r ;
    Info->orbit->x[0] = Info->x[0] ;
    Info->orbit->y[0] = Info->y[0] ;
    Info->orbit->z[0] = Info->z[0] ;
}


void SetZero(Planet *Info, int num, int OrbitNum)//�Թ켣������г�ʼ��
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


WORLD GetPlaNum(char sInfoFileName[])//���ļ��л�ȡ��ʼ��Ϣ
{
    FILE *fp ;
    WORLD world ;
    fp = fopen( sInfoFileName, "r") ;     //���ļ�
    if(fp==NULL)
    {
        ErrorBox("Can not find info.dat");//���ļ���ʧ�ܱ���
        world.PlanetQty = 0 ;
        return world ;
    }

    fscanf( fp, "%d", &world.Multiply) ;  //��ȡ�����ᵥλ����
    fscanf( fp, "%d", &world.Orbit) ;     //��ȡ�켣�ĳ���
    fscanf( fp, "%d", &world.PlanetQty) ; //��ȡ���ǵ�����
    fscanf( fp, "%le", &world.CalRate) ;  //��ȡ����Ƶ��
    fscanf( fp, "%le", &world.G) ;        //���������������
    fscanf( fp, "%le", &world.StepSize) ; //��ȡ���㲽��

    fclose( fp) ;                         //�ر��ļ�

    return world ;                        //��������������Ϣ
}


int GetPlaInfo(Planet *Info, char sInfoFileName[], int num)//���ļ��л�ȡ�������ݣ�������������
{
    double x, y, z, Vx, Vy, Vz, r, m ;//���ڴ洢���ļ��ж���������
    FILE *fp ;
    WORLD world ;
    fp = fopen( sInfoFileName, "r") ;//���ļ�
    if(fp==NULL)
    {
        ErrorBox("GetPlaInfo Error");//���ļ���ʧ�ܱ���
        return 0 ;
    }

    fscanf( fp, "%d", &world.Multiply) ;  //��ȡ�����ᵥλ����
    fscanf( fp, "%d", &world.Orbit) ;     //��ȡ�켣�ĳ���
    fscanf( fp, "%d", &world.PlanetQty) ; //��ȡ���ǵ�����
    fscanf( fp, "%le", &world.CalRate) ;  //��ȡ����Ƶ��
    fscanf( fp, "%le", &world.G) ;        //���������������
    fscanf( fp, "%le", &world.StepSize) ; //��ȡ���㲽��

    for(int i = 0; i<num; ++i)
    {
        fscanf( fp, "%lf%lf%lf%lf%lf%lf%lf%lf",
               &r, &m, &Vx, &Vy, &Vz, &x, &y, &z) ;//������ÿ8��һ�����
        Info->r = (long double)r, Info->m = (long double)m ;
        Info->V[0] = (long double)Vx, Info->V[1] = (long double)Vy,  Info->V[2] = (long double)Vz ;
        Info->x[0] = (long double)x, Info->y[0] = (long double)y, Info->z[0] = (long double)z ;//�����������ݴ�������ڵ���
        Info = Info->next ;//�ڵ������ƶ�һλ
    }

    return 1 ;
}


void SetDefaultInfo(Planet *Info)//�������� info.dat �ļ�ʱ ʹ�ô˺����趨Ĭ����ֵ �����յ����ȶ�ϵͳ
{
    double i = 1 ;
    double l = 0;
    Info->r = l+i*695.55, Info->m = 1989000 ;
    Info->V[0] = 0, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 0 ;              //̫������
    Info = Info->next ;

    Info->r = l+i*2.44, Info->m = 0.3302 ;
    Info->V[0] = 0.05896, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 46001.2 ;        //ˮ������
    Info = Info->next ;

    Info->r = l+i*2.44, Info->m = 4.869 ;
    Info->V[0] = 0.035258, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 107476.259 ;     //��������
    Info = Info->next ;

    Info->r = l+i*6.378, Info->m = 6 ;
    Info->V[0] = 0.029, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 152097.7 ;       //��������
    Info = Info->next ;

    Info->r = l+i*6.7, Info->m = 0.64219 ;
    Info->V[0] = 0.026499, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 206644.545 ;     //��������
    Info = Info->next ;

    Info->r = l+i*71.4935, Info->m = 1900 ;
    Info->V[0] = 0.013719, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 740520 ;         //ľ������
    Info = Info->next ;

    Info->r = l+i*60.268, Info->m = 569 ;
    Info->V[0] = 0.010175, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 1353572.956 ;    //��������
    Info = Info->next ;

    Info->r = l+i*52, Info->m = 86.81 ;
    Info->V[0] = 0.0071, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 2748938.461 ;    //��������
    Info = Info->next ;

    Info->r = l+i*24.766, Info->m = 102.47 ;
    Info->V[0] = 0.0054899, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 0, Info->z[0] = 4452940.833 ;    //��������
    Info = Info->next ;

    Info->r = l+i*1.737, Info->m = 0.07349 ;
    Info->V[0] = 0.03, Info->V[1] = 0, Info->V[2] = 0 ;
    Info->x[0] = 0, Info->y[0] = 384.4, Info->z[0] = 152097.7 ;   //��������

    Info = Info->next ;

}


void SetDefaultWorld(WORLD *WorldInfo)
{
    WorldInfo->PlanetQty = 10 ;     //�趨��������
    WorldInfo->Multiply = 150000 ; //�趨����ϵ��λ����
    WorldInfo->Orbit = 100000 ;  //�趨�켣�㳤��
    WorldInfo->CalRate = 1E5 ;     //�趨���㲽��
    WorldInfo->StepSize = 2 ;      //�趨ʱ�䲽��Ϊ 1s
    WorldInfo->G = 6.67E-5 ;       //�趨������������


}


AUX_RGBImageRec *LoadBMP(char *Filename)// ����λͼͼ��
{
	FILE *File=NULL;	// �ļ����
	if (!Filename)		// ȷ���ļ������ṩ
	{
		return NULL;	// ���û�ṩ������ NULL
	}
	File=fopen( Filename,"r");	// ���Դ��ļ�
	if (File)					// ����ļ�����
	{
		fclose(File);						// �رվ��
		return auxDIBImageLoad(Filename);	// ����λͼ������ָ��
	}
	return NULL;							// �������ʧ�ܣ����� NULL
}


int LoadGLTextures(GLuint *texture, char *Filename)// ����λͼ��ת��������
{
    if (!Filename)	//ȷ���ļ������ṩ
	{
		return 0 ;	//���û�ṩ������ 0
	}
	AUX_RGBImageRec *TextureImage[1] ;            //��������Ĵ洢�ռ�
	memset(TextureImage,0,sizeof(void *)*1);
	TextureImage[0] = LoadBMP(Filename) ;         //����λͼ

    if(!TextureImage[0])
    {
        *texture = 0 ;
        _beginthread( ErrorMsg, 0, Filename) ;    //���������߳�
        return 0 ;
    }

	if(TextureImage)
    {
        glGenTextures( 1, texture) ;                                    //��������
        glBindTexture(GL_TEXTURE_2D, *texture);

        //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//�����˲�
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	//�����˲�


        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
    }
    else
    {
        return 0 ;
    }

    free(TextureImage[0]->data) ;//�ͷ�����ͼ��ռ�õ��ڴ�
    free(TextureImage[0]);       // �ͷ�ͼ��ṹ

	return 1 ;
}







/*
GLuint *LoadGLTextures(void)//����Դ�ļ�����ͼ��ת��Ϊ����
{

	HBITMAP hBMP;//λͼ���
	BITMAP	BMP; //λͼ�ṹ


    glGenTextures( 3, &gluTexture[0]);//����3������
    //hBMP = LoadBitmap ( GetModuleHandle(NULL), MAKEINTRESOURCE (IDB_BITMAP1) );
    hBMP = (HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//��λͼ�ɹ�����ʱ
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//��ȡλͼ
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//�����ֽڷ�ʽ�����ڴ�
        glBindTexture( GL_TEXTURE_2D, gluTexture[0]) ;//��λͼ
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//�����˲�
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//�����˲�

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//��������
        DeleteObject(hBMP);	//ɾ��λͼ����
    }
    else
    {
        MessageBox( NULL, "ERROR", "ERROR", MB_OK) ;
    }

    hBMP=(HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//��λͼ�ɹ�����ʱ
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//��ȡλͼ
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//�����ֽڷ�ʽ�����ڴ�
        glBindTexture( GL_TEXTURE_2D, gluTexture[1]) ;//��λͼ
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//�����˲�
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//�����˲�

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//��������
        DeleteObject(hBMP);	//ɾ��λͼ����
    }

    hBMP=(HBITMAP)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
    if (hBMP)//��λͼ�ɹ�����ʱ
    {
        GetObject( hBMP, sizeof(BMP), &BMP) ;//��ȡλͼ
        glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;//�����ֽڷ�ʽ�����ڴ�
        glBindTexture( GL_TEXTURE_2D, gluTexture[2]) ;//��λͼ
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) ;//�����˲�
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) ;//�����˲�

        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits) ;//��������
        DeleteObject(hBMP);	//ɾ��λͼ����
    }
    return NULL ;
}

*/



void SaveBmp( GLint x, GLint y, GLint height, GLint width)
{
    int BmpSize = height*width*3 ;
    int Completion = 4 - width%4 ;            //bmp�п�ȱ���Ϊ4�ı��� �����������Ҫ���Ӷ��ٲſɳ�Ϊ 4 �ı���
    BmpSize += height*Completion ;            //��ÿ�еĿ�Ƚ������

    BITMAPFILEHEADER BmpHeader = { 0x4D42,    //ָ���ļ�����Ϊ BM
                                   54+BmpSize,//����BMP�ļ��Ĵ�С
                                   0,         //�˴�����Ϊ0
                                   0,         //�˴�����Ϊ0
                                   54         //˵�����ļ�ͷ0000h��ʼ��ͼ���������ݵ��ֽ�ƫ���������ֽ�BytesΪ��λ��
                                    } ;

    BITMAPINFOHEADER BmpInfoHeader = { 0x28,  //ͼ��������Ϣ��Ĵ�С����Ϊ28H
                                       width, //ͼ���ȣ�������Ϊ��λ
                                       height,//ͼ��߶�
                                       1,     //ͼ���plane��������Ϊ1
                                       24,    //��¼���ص�λ��
                                       0,     //����ѹ����ʽ 0Ϊ��ѹ��
                                       0,     //ͼ�������ݵĴ�С����λ�ֽڣ�����������4�ı���
                                       0,     //ˮƽÿ���ж������أ����豸�޹�λͼ�У�ÿ�ֽ���00H��д
                                       0,     //��ֱÿ���ж������أ����豸�޹�λͼ�У�ÿ�ֽ���00H��д
                                       0,     //��ͼ�����õ���ɫ��
                                       0,     //ָ����Ҫ����ɫ������Ϊ0ʱ����ʾ������ɫһ����Ҫ
                                        } ;

    GLubyte *bmp = (GLubyte *)malloc(BmpSize) ;                            //bmp���ڴ洢λͼ��Ϣ
    glPixelStorei( GL_UNPACK_ALIGNMENT, 4) ;                               //��֡�������4λ����
    glReadPixels( x, y, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp) ;//��֡�����ж���λͼ



    time_t t ;
    time(&t);//��ȡ��ǰʱ��
    struct tm *p ;
    p = localtime(&t) ;//����ǰʱ��ת��Ϊ����ʱ��
    char str[50] ;
    sprintf( str, "%d%d%d%d%d%d.bmp", p->tm_year+1900, p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec) ;//����ʱ�����׵��ļ���д���ַ���
    FILE *fp = fopen( str, "wb") ;
    fwrite( &BmpHeader, sizeof(BmpHeader), 1, fp) ;
    fwrite( &BmpInfoHeader, sizeof(BmpInfoHeader), 1, fp) ;
    fwrite( bmp, BmpSize*sizeof(GLubyte), 1, fp) ;

    fclose(fp);//�ر��ļ�
    free(bmp);//�ͷ��ڴ�
}









































































