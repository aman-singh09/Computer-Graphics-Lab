#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>
#include<stdio.h>

void d_pixel(int x, int y)
{
    glColor3f(1,0,0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void plot(int x, int y ,int h, int k)
{

    d_pixel(x+h,y+k);
    d_pixel(-x+h,y+k);
    d_pixel(x+h,-y+k);
    d_pixel(-x+h,-y+k);
    d_pixel(y+h,x+k);
    d_pixel(-y+h,x+k);
    d_pixel(y+h,-x+k);
    d_pixel(-y+h,-x+k);
}
void circle(int h,int k, int r)
{

    int d=1-r,x=0,y=r;
    while(y>x)
    {
        if(d<0)
        {

            x++;
            d+=(2*x)+3;
        }
        else
        {
            d+=(2*(x-y)+4);
            x++;
            y--;
        }
        plot(x,y,h,k);
    }
}
void display()
{

    int h=250,k=250,r=150;
    glClearColor(1,1,1,0);
    circle(h,k,r);
    glFlush();
}
void myInit()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Midpoint Circle -- Aman Kumar (016)");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}
