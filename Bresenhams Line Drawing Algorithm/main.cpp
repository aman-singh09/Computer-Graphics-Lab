#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>

int a,b,c,d;

void draw_pixels(int x,int y)
{
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void bresenhams(int x1,int y1,int x2,int y2)
{
    int dx=x2-x1,dy=y2-y1;
    if(dx<0) dx=-dx;
    if(dy<0) dy= -dy;
    
    
    if (dy < dx)
    {
    int P=2*dy-dx;
    int pneg=2*dy;
    int Ppos=2*(dy-dx);
    
    if(x1>x2)
    {
        int temp;
        temp=x1;
        x1=x2;
        x2=temp;
        
        temp=y1;
        y1=y2;
        y2=temp;
    }
    
    int x=x1;
    int y=y1;
    int yinc=1;
    if (y2<y1) yinc= -1;
    draw_pixels(x,y);
    for(int k=0;k<dx;k++)
    {
        x++;
        if(P<0)
        {
            P = P + pneg;
        }
        else{
            y= y+ yinc;
            P= P+Ppos;
        }
        draw_pixels(x,y);
    }
    }
    else{
        int P=2*dx-dy;
        int pneg=2*dx;
        int Ppos=2*(dx-dy);
        
        if(y1>y2)
        {
            int temp;
            temp=x1;
            x1=x2;
            x2=temp;
            
            temp=y1;
            y1=y2;
            y2=temp;
        }
        
        int x=x1;
        int y=y1;
        int xinc=1;
        if (x2<x1) xinc= -1;
        draw_pixels(x,y);
        for(int k=0;k<dy;k++)
        {
            y++;
            if(P<0)
            {
                P = P + pneg;
            }
            else{
                x= x+ xinc;
                P= P+Ppos;
            }
            draw_pixels(x,y);
        }
    }
}
void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    bresenhams(a,b,c,d);
    
    glColor3f(0,0,1);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2f(a,b);
    glVertex2f(c,d);
    glEnd();
       glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    printf("Enter end points of line(x0,y0) and (x1,y1):\n ");
    scanf("%d%d%d%d",&a,&b,&c,&d);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(500,500);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Bresenhams line Drawing - Aman Kumar (016)");

    glutDisplayFunc(display);
    init();

    glutMainLoop();
}
// 100 100 400 400
// 100 100 400 200
// 100 400 400 300
// 100 100 200 400
// 100 400 300 100
// 100 100 400 100
// 100 100 100 400
