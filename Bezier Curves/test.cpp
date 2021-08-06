#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
float theta = 0;
float rad = 3.14 / 180;
int id = 0, flag = 1;
int fact(int num)
{
    int sum = 1;
    for (int i = num; i >= 1; i--)
        sum *= i;
    return sum;
}
void combination(int n, int c[4])
{
    for (int k = 0; k <= n; k++)
        c[k] = fact(n) / (fact(k) * fact(n - k));
}
void curve(float cp[4][2])
{
    int n = 3, c[4];
    float x, y;
    combination(n, c);
    glBegin(GL_LINE_STRIP);
    for (float u = 0; u <= 1; u += 0.05)
    {
        x = 0;
        y = 0;
        for (int k = 0; k <= n; k++)
        {
            x += cp[k][0] * c[k] * pow(u, k) * pow(1 - u, n - k);
            y += cp[k][1] * c[k] * pow(u, k) * pow(1 - u, n - k);
        }
        glVertex2f(x, y);
    }
    glEnd();
}
void display()
{
    float cp[4][2] = {{200, 400}, {240, 420}, {270, 380}, {300, 400}};
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (flag == 1)
    {
        cp[1][0] += sin(theta * rad);
        cp[1][1] += sin(theta * rad);
        cp[2][0] += sin(theta * rad);
        cp[2][1] += sin(theta * rad);
        cp[3][0] += sin(theta * rad);
        cp[3][1] += sin(theta * rad);
        theta += 5;
    }
    if (id == 1)
    {
        glPushMatrix();
        glLineWidth(4);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(200, 400);
        glVertex2f(200, 200);
        glEnd();
        glColor3f(1, 0.5, 0);
        for (int i = 0; i < 10; i++)
        {
            glTranslatef(0, -2, 0);
            curve(cp);
        }
        glColor3f(1, 1, 1);
        for (int i = 0; i < 10; i++)
        {
            glTranslatef(0, -2, 0);
            curve(cp);
        }
        glColor3f(0, 1, 0);

        for (int i = 0; i < 10; i++)
        {
            glTranslatef(0, -2, 0);
            curve(cp);
        }
        glPopMatrix();
    }
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}
void menu(int num)
{
    if (num == 10)
        id = 1;
    if (num == 20)
        flag = 1;
    else
        flag = 0;
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Beizer - Aman Kumar(016)");
    glutDisplayFunc(display);
    init();
    glutCreateMenu(menu);
    glutAddMenuEntry("Display flag", 10);
    glutAddMenuEntry("start animation", 20);
    glutAddMenuEntry("stop animation", 30);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();

    return 0;
}
