#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/glut.h>
#include <stdio.h>
float vertices[8][3] = {{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1}, {1, -1, 1}, {-1, -1, 1}};
float theta[3] = {0, 0, 0};
int axis = 0;
float viewer[3] = {0, 0, 5};
void polygon(int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
    glEnd();
}
void colorcube()
{
    glColor3f(1, 1, 0);
    polygon(0, 1, 2, 3);
    glColor3f(1, 0, 0);  //back
    polygon(1, 2, 5, 6); //right
    glColor3f(0, 1, 0);
    polygon(4, 5, 6, 7); //front
    glColor3f(0, 0, 1);
    polygon(0, 3, 4, 7); //left
    glColor3f(0, 1, 1);
    polygon(4, 3, 2, 5); //top
    glColor3f(0, 0, 0);
    polygon(0, 1, 6, 7); //bottom
}
void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);
    glRotatef(theta[0], 1, 0, 0);
    glRotatef(theta[1], 0, 1, 0);
    glRotatef(theta[2], 0, 0, 1);
    colorcube();
    glFlush();
    glutSwapBuffers();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    //glOrtho(-2,2,-2,2,-2,2);
    glFrustum(-2, 2, -2, 2, 2, 10);
    glMatrixMode(GL_MODELVIEW);
}
void spincube()
{
    theta[axis] += 0.5;
    if (theta[axis] > 360)
        theta[axis] = 0;
    glutPostRedisplay();
}
void mymouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
    spincube();
}
void mykeys(unsigned char keys, int x, int y)
{
    if (keys == 'X')
        viewer[0] -= 1;
    if (keys == 'x')
        viewer[0] += 1;
    if (keys == 'Z')
        viewer[2] -= 1;
    if (keys == 'z')
        viewer[2] += 1;
    if (keys == 'Y')
        viewer[1] -= 1;
    if (keys == 'y')
        viewer[1] += 1;
    glutPostRedisplay();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Perspective Cube - Aman Kumar(016)");
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);

    glutKeyboardFunc(mykeys);
    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
