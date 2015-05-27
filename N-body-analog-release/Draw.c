#include "Fun.h"

/* Whirl ����*/
void Whirl(GLdouble *Xrot, GLdouble *Yrot, GLdouble *Deep, Planet *Info, int num, double Near, double Far)//���ڽ����ӽ���ת
{

    glLoadIdentity();//���õ�ǰ��ģ�͹۲����

    if(*Deep>-Near)  //�����ӽ����
    {
        *Deep = -Near ;
    }
    else if(*Deep<-Far)
    {
        *Deep = -Far ;
    }
    if( num > -1)
    {
        for(int i = 0; i<num; ++i)
        {
            Info = Info->next ;
        }

        if(*Deep>-(Info->r+Near))
        {
            *Deep = -Info->r-Near ;
        }
    }



    glTranslated( 0, 0, *Deep) ;
    glRotated( *Xrot, 1, 0, 0) ;
    glRotated( *Yrot, 0, 1, 0) ;
    if( num > -1)
    {
        glTranslated( -Info->orbit->x[0], -Info->orbit->y[0], -Info->orbit->z[0]) ;
    }

}


void DrawCS(int length)//����һ��ֱ������ϵ
{
    int i ;//����for�ṹ����
    glColor4f( 0, 0.2, 0.2, 0.1);     // Alpha ���
    //��������ϵ
    glBegin(GL_LINES);
        //����X-Yƽ������
        for( i = -10; i <= 10; i++)   //��Yƽ�е�����
        {
            if(i==0)
            {
                glVertex3f( i*length, 0, 0) ;
                glVertex3f( i*length, 0, -10*length) ;
                continue;
            }

            glVertex3f( i*length, 0, 10*length) ;
            glVertex3f( i*length, 0, -10*length) ;
        }
        for( i =- 10; i <= 10; i++)//��Xƽ�е�����
        {
            if(i == 0)
            {
                glVertex3f( 0, 0, i*length) ;
                glVertex3f( -10*length, 0, i*length) ;
                continue;
            }
            glVertex3f( 10*length, 0, i*length) ;
            glVertex3f( -10*length, 0, i*length) ;
        }

        glColor3f( 0, 1, 1) ;   //����X-Y-Z������
        glVertex3f( 0, 0, 0) ;
        glVertex3f( 0, 0, 12*length) ;//����Z������

        glVertex3f( 0, 0, 0) ;
        glVertex3f( 0, 12*length, 0) ;//����Y������

        glVertex3f( 0, 0, 0) ;
        glVertex3f( 12*length, 0, 0) ;//����X������

    glEnd();
    glColor3f( 0, 1, 0) ;

    glPushMatrix();//����Z���ϵļ�ͷ
    glTranslated( 0, 0, 10.5*length) ;
    glRotated( 90, 1, 0, 0) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

    glPushMatrix();//����Y���ϵļ�ͷ
    glTranslated( 0, 10.5*length, 0) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

    glPushMatrix();//����X���ϵļ�ͷ
    glTranslated( 10.5*length, 0, 0) ;
    glRotated( -90, 0, 0, 1) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

}


void DrawPlanet(Planet *Info)//�ڵ�ǰλ�û���һ������
{
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glutWireSphere( Info->orbit->r, 20, 20) ;                               //�������ǵ� r ����һ���߿���
    glPopMatrix();                                                          //�ָ�����һ�α������Ϣ
}


void DrawOrbit(Planet *Info, int OrbitNum)//�������ǹ켣
{
    glBegin(GL_LINE_STRIP);
        for(int j = 0; j<OrbitNum; ++j)
        {
            glColor3f( 1-(float)j/OrbitNum, 0.5, 0) ;
            glVertex3d( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;
            Info->orbit = Info->orbit->previous ;
        }
    glEnd();

}


void DrawSun(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ��̫��
{
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                                            //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;                           //ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;                           //�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                                           //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;                           //�������ǵ� r ����һ��������������
    }
    glPopMatrix();                                                          //�ָ�����һ�α������Ϣ
}


void DrawMercury(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ��ˮ��
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawVenus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawEarth(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawMars(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawJupiter(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ��ľ��
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawSaturn(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawUranus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ��������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawNeptune(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ��������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }


    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawMoon(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//�ڵ�ǰλ�û���һ������
{
    static GLdouble y ;//������ת
    if( y > 360 )      //�� y ���е��� ��ֹ������߹�С
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }

    glColor3f( 1, 1, 1) ;                                                   //����ɫ����Ϊ��ɫ
    glPushMatrix();                                                         //���浱ǰ��Ϣ
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//�ƶ������ǵ�����
    glRotated( -60, 1, 0, 0) ;                                              //���е����ƫת�����������������Ҫ��״̬
    if(!Pause)                                                              //���� Pause �ж��Ƿ�����ͣ״̬
    {
        glRotated( y++, 0, 0, 1) ;                                          //��û������ͣ״̬ ������ת
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //������ͣ״̬ ֹͣ��ת ���ֵ�ǰ״̬
    }
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//�������ǵ� r ����һ��������������
    }
    glPopMatrix();                               //�ָ�����һ�α������Ϣ
}


void DrawUniverse(GLUquadricObj *qua, GLuint *texture)//�������汳��
{
    glColor3f( 1, 1, 1) ;                        //����ɫ����Ϊ��ɫ
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //��������
        glBindTexture( GL_TEXTURE_2D, *texture) ;//ѡ������
        gluSphere( qua, 1.5E7, 360, 360) ;       //����һ��������������
        glDisable(GL_TEXTURE_2D);                //�ر�����
    }
    else
    {
        gluSphere( qua, 1.5E7, 360, 360) ;       //����һ��������������
    }

}


void DrawArrow( GLfloat hight, GLfloat width)//����һ����ͷ
{
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f( -width, 0, width) ;
        glVertex3f( -width, 0, -width) ;
        glVertex3f( 0, hight, 0) ;
        glVertex3f( width, 0, -width) ;
        glVertex3f( width, 0, width) ;
        glVertex3f( -width, 0, width) ;
    glEnd();
}

















