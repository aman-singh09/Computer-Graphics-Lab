#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>

float v[8][3] = {{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1},{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1}};
                    
static float theta[3]={0.0,0.0,0.0};
int axis=2;

void cube(int a,int b,int c, int d){
    glBegin(GL_POLYGON);
        glVertex3fv(v[a]);
        glVertex3fv(v[b]);
        glVertex3fv(v[c]);
        glVertex3fv(v[d]);
    glEnd();
}

void colorcube(){
    glColor3f(1,0,0);
    cube(4,5,1,0);
    glColor3f(0,1,0);
    cube(7,6,2,3);
    glColor3f(0,0,1);
    cube(6,5,1,2);
    glColor3f(1,1,0);
    cube(7,4,0,3);
    glColor3f(1,0,1);
    cube(0,1,2,3);
    glColor3f(0,1,1);
    cube(4,5,6,7);
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  glRotatef(theta[0],1.0,0.0,0.0);
  glRotatef(theta[1],0.0,1.0,0.0);
  glRotatef(theta[2],0.0,0.0,1.0);
  colorcube();
  glFlush();
  glutSwapBuffers();
}

void spinCube()
{
    theta[axis]+=1.0;
    if(theta[axis]>360.0)
        theta[axis]-=360.0;
    display();
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        axis=0;
    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
        axis=1;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        axis=2;
}

void init()
{

    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity();
    glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Spin a color cube - Aman Kumar (016)");
    
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
}
