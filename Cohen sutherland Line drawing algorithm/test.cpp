#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
float a, b, c, d;
//float a = 40, b = 60, c = 180, d = 80;
//float a=100,b=150,c=200,d=80;
//float a=60,b=40,c=120,d=120;
//float a=60,b=60,c=120,d=80;
//float a=60,b=60,c=120,d=120;
int xmin = 50, xmax = 150, ymin = 50, ymax = 100;
const int RIGHT = 8, LEFT = 2, TOP = 4, BOTTOM = 1;
int code0, code1, codeout;
int computeoutcode(float x, float y)
{
    int code = 0;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    return code;
}
void cohen(float a, float b, float c, float d)
{
    bool accept = false, done = false;
    code0 = computeoutcode(a, b);
    code1 = computeoutcode(c, d); //printf("OC1= %d OC2= %d",code0,code1);
    do
    {
        if ((code0 | code1) == 0)
        {
            done = true;
            accept = true;
        }
        else if (code0 & code1)
        {
            done = true;
        }
        else
        {
            double x, y;
            codeout = code0 ? code0 : code1;
            if (codeout & TOP)
            {
                x = a + (c - a) * (ymax - b) / (d - b);
                y = ymax;
            }
            else if (codeout & BOTTOM)
            {
                x = a + (c - a) * (ymin - b) / (d - b);
                y = ymin;
            }
            else if (codeout & LEFT)
            {
                x = xmin;
                y = b + (d - b) * (xmin - a) / (c - a);
            }
            else
            {
                x = xmax;
                y = b + (d - b) * (xmax - a) / (c - a);
            }
            if (codeout == code0)
            {
                a = x;
                b = y;
                code0 = computeoutcode(a, b);
            }
            else if (codeout == code1)
            {
                c = x;
                d = y;

                code1 = computeoutcode(c, d);
            }
        }
    } while (!done);
    glTranslatef(150, 150, 0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    if (accept)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(a, b);
        glVertex2i(c, d);
        glEnd();
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(a, b);
    glVertex2i(c, d);
    glEnd();
    cohen(a, b, c, d);
    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    printf("Enter the values\n");
    scanf("%f%f%f%f", &a, &b, &c, &d);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen Sutherland Line clipping - Aman Kumar (016)");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
