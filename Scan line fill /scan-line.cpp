#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>

float x1,x2,x3,x4,y1,y2,y3,y4;
float le[500],re[500];
int flag=0;

void edge(float x1,float y1,float x2,float y2)
{
    float m,x;
    int i;
    if(y1>y2)
    {
        float temp;
        temp=x1;
        x1=x2;
        x2=temp;
        
        temp=y1;
        y1=y2;
        y2=temp;
    }
    m=(y2-y1)/(x2-x1);
    x=x1;
    for(i=y1;i<y2;i++)
    {
        if(x<le[i])
            le[i]=x;
        
        if(x>re[i])
            re[i]=x;
        
        x+=(1/m);
    }
}


void scanfill(float x1,float x2,float x3,float x4,float y1,float y2,float y3,float y4)
{
    int i,j;
    
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }
    
    edge(x1,y1,x2,y2);
    edge(x2,y2,x3,y3);
    edge(x3,y3,x4,y4);
    edge(x4,y4,x1,y1);

    for(i=0;i<500;i++)
    {
        if(le[i]<re[i])
        {
            for(j=le[i]-1;j<=re[i];j++)
            {
                glColor3f(0,0,1);
                glBegin(GL_POINTS);
                    glVertex2f(j,i);
                glEnd();
            }
        }
    }
    
}


void display()
{
    x1=200;y1=200;x2=100;y2=300;x3=200;y3=400;x4=300;y4=300;
    
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(x1,y1);
    glVertex2d(x2,y2);
    glVertex2d(x3,y3);
    glVertex2d(x4,y4);
    glEnd();
    
    if(flag==1)
    {
        scanfill(x1,x2,x3,x4,y1,y2,y3,y4);
    }
    
    glFlush();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

void scanmenu(int id)
{
    if(id==1)
        flag=1;
    
    if(id==2)
        flag=0;
    
    if(id==3)
        exit(0);
    
    display();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(480,480);
    glutCreateWindow("Scan Line algorithm - Aman Kumar(016)");
    glutDisplayFunc(display);
    myinit();
    
    glutCreateMenu(scanmenu);
    glutAddMenuEntry("Fill the polygon", 1);
    glutAddMenuEntry("Outline",2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
}
