#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>
#include <stdio.h>
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(float x1, float y1, float x2, float y2)
{
    float dy, dx, step, x, y, k, xin, yin;
    dx = x2 - x1;
    dy = y2 - y1;
    printf("m : %f", dy / dx);
    if (abs(dx) > abs(dy))
    {
        step = abs(dx);
    }
    else
        step = abs(dy);
    xin = dx / step;
    yin = dy / step;
    x = x1;
    y = y1;
    draw_pixel(abs(x), abs(y));
    for (k = 1; k <= step; k++)
    {
        x = x + xin;
        y = y + yin;
        draw_pixel(abs(x), abs(y));
    }
}
void display()
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(3.0);
    //DDA(200,100,100,400);
    //DDA(200,100,100,400);
    //DDA(100,100,200,400);
    //DDA(100,100,400,300);
    DDA(100,400,400,300);
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DDA Line Drawing - Aman Kumar (016)");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();
}
