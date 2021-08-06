#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>
#include<stdio.h>


void wall(float thickness)
{
    glPushMatrix();
        glTranslatef(0.5,0,0.5);
        glScalef(1,thickness,1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void tableleg(float legthickness, float leglenth)
{
    glPushMatrix();
        glScalef(legthickness,leglenth,legthickness);
        glutSolidCube(1.0);
    glPopMatrix();
}

void table(float topwidth, float topthickness,float legthickness, float leglenth)
{
    glPushMatrix();
        glTranslatef(0,leglenth/2,0);
        glScalef(topwidth,topthickness,topwidth);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.3,0,0.3);
        tableleg(legthickness,leglenth);
        glTranslatef(-0.6,0,0);
        tableleg(legthickness,leglenth);
        glTranslatef(0,0,-0.6);
        tableleg(legthickness,leglenth);
        glTranslatef(0.6,0,0);
        tableleg(legthickness,leglenth);
    glPopMatrix();
}

void display(void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float light_pos[] = {2,4,3,1};
    float light_intensitiy[] = {1,1,1,1};
    float mat_amb[] = {1,1,1,1};


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_intensitiy);


    glLoadIdentity();

    gluLookAt(2,2,2,0,0,0,0,1,0);

    glPushMatrix();
        glTranslatef(0.5,0.4,0.5);
        table(0.8,0.05,0.05,0.5);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.8,1.0,0.8);
        glutSolidTeapot(0.15);
    glPopMatrix();

    glPushMatrix();
        wall(0.05);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-90,1,0,0);
        wall(0.05);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90,0,0,1);
        wall(0.05);
    glPopMatrix();


    glFlush();
}

void init()
{

    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    glOrtho(-1,1,-1,1,1,5);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1000,500);
    glutInitWindowPosition(20,20);
    glutCreateWindow("Table - Aman Kumar (016)");


    glutDisplayFunc(display);
    init();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
