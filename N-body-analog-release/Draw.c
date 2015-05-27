#include "Fun.h"

/* Whirl 函数*/
void Whirl(GLdouble *Xrot, GLdouble *Yrot, GLdouble *Deep, Planet *Info, int num, double Near, double Far)//用于进行视角旋转
{

    glLoadIdentity();//重置当前的模型观察矩阵

    if(*Deep>-Near)  //限制视角深度
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


void DrawCS(int length)//绘制一个直角坐标系
{
    int i ;//用于for结构计数
    glColor4f( 0, 0.2, 0.2, 0.1);     // Alpha 混合
    //绘制坐标系
    glBegin(GL_LINES);
        //绘制X-Y平面网格
        for( i = -10; i <= 10; i++)   //与Y平行的网线
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
        for( i =- 10; i <= 10; i++)//与X平行的网线
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

        glColor3f( 0, 1, 1) ;   //绘制X-Y-Z坐标轴
        glVertex3f( 0, 0, 0) ;
        glVertex3f( 0, 0, 12*length) ;//绘制Z轴坐标

        glVertex3f( 0, 0, 0) ;
        glVertex3f( 0, 12*length, 0) ;//绘制Y轴坐标

        glVertex3f( 0, 0, 0) ;
        glVertex3f( 12*length, 0, 0) ;//绘制X轴坐标

    glEnd();
    glColor3f( 0, 1, 0) ;

    glPushMatrix();//绘制Z轴上的箭头
    glTranslated( 0, 0, 10.5*length) ;
    glRotated( 90, 1, 0, 0) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

    glPushMatrix();//绘制Y轴上的箭头
    glTranslated( 0, 10.5*length, 0) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

    glPushMatrix();//绘制X轴上的箭头
    glTranslated( 10.5*length, 0, 0) ;
    glRotated( -90, 0, 0, 1) ;
    DrawArrow( 1.5*length, 0.1*length) ;
    glPopMatrix();

}


void DrawPlanet(Planet *Info)//在当前位置绘制一个行星
{
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glutWireSphere( Info->orbit->r, 20, 20) ;                               //根据行星的 r 绘制一个线框球
    glPopMatrix();                                                          //恢复到上一次保存的信息
}


void DrawOrbit(Planet *Info, int OrbitNum)//绘制行星轨迹
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


void DrawSun(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个太阳
{
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                                            //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;                           //选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;                           //根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                                           //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;                           //根据行星的 r 绘制一个二次曲面球体
    }
    glPopMatrix();                                                          //恢复到上一次保存的信息
}


void DrawMercury(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个水星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawVenus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个金星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawEarth(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个地球
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawMars(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个火星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawJupiter(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个木星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawSaturn(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个土星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawUranus(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个天王星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawNeptune(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个海王星
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }
    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }

    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }


    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawMoon(Planet *Info, GLUquadricObj *qua, GLuint *texture, BOOL Pause)//在当前位置绘制一个月球
{
    static GLdouble y ;//用于自转
    if( y > 360 )      //对 y 进行调整 防止过大或者过小
    {
        y -= 360 ;
    }
    else if( y < -360 )
    {
        y += 360 ;
    }

    glColor3f( 1, 1, 1) ;                                                   //将颜色设置为白色
    glPushMatrix();                                                         //保存当前信息
    glTranslated( Info->orbit->x[0], Info->orbit->y[0], Info->orbit->z[0]) ;//移动到行星的坐标
    glRotated( -60, 1, 0, 0) ;                                              //进行地轴的偏转，并将纹理调整至想要的状态
    if(!Pause)                                                              //根据 Pause 判断是否处于暂停状态
    {
        glRotated( y++, 0, 0, 1) ;                                          //若没有在暂停状态 进行自转
    }
    else
    {
        glRotated( y, 0, 0, 1) ;                                            //若在暂停状态 停止自转 保持当前状态
    }
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, Info->orbit->r, 36, 36) ;//根据行星的 r 绘制一个二次曲面球体
    }
    glPopMatrix();                               //恢复到上一次保存的信息
}


void DrawUniverse(GLUquadricObj *qua, GLuint *texture)//绘制宇宙背景
{
    glColor3f( 1, 1, 1) ;                        //将颜色设置为白色
    if(*texture)
    {
        glEnable(GL_TEXTURE_2D);                 //开启纹理
        glBindTexture( GL_TEXTURE_2D, *texture) ;//选择纹理
        gluSphere( qua, 1.5E7, 360, 360) ;       //绘制一个二次曲面球体
        glDisable(GL_TEXTURE_2D);                //关闭纹理
    }
    else
    {
        gluSphere( qua, 1.5E7, 360, 360) ;       //绘制一个二次曲面球体
    }

}


void DrawArrow( GLfloat hight, GLfloat width)//绘制一个箭头
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

















