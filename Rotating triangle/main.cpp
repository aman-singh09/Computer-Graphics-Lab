#define GL_SILENCE_DEPRECATION
#include<stdio.h>
#include<iostream>
#include<GLUT/glut.h>
#include<math.h>
#define pi 3.142857

// function to initialize
void init (void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,500,-100,500);
    glMatrixMode(GL_MODELVIEW);
}

float triangle[3][3] = {{100,200,150},{100,100,200},{1,1,1}};
float rot_mat[3][3] = {{0},{0},{0}};
float result[3][3] = {{0},{0},{0}};

float h= 0,k=0;
float m=0,n=0;
float theta;


void drawTriangle(float a[3][3])
{
    glBegin(GL_TRIANGLES);
        glVertex2f(a[0][0],a[1][0]);
        glVertex2f(a[0][1],a[1][1]);
        glVertex2f(a[0][2],a[1][2]);
    glEnd();
}


void multiply()
{
    int i,j,l;
    for(i=0;i<3;++i)
    {
        for(j=0;j<3;++j)
        {
            result[i][j] = 0;
            for(l=0;l<3;++l)
            {
                result[i][j] = result[i][j] + (rot_mat[i][l]*triangle[l][j]);
            }
        }
    }
}
void rrotate(float m,float n)
{
    rot_mat[0][0] = cos(theta);
    rot_mat[0][1] = -sin(theta);
    rot_mat[0][2] = m;

    rot_mat[1][0] = sin(theta);
    rot_mat[1][1] = cos(theta);
    rot_mat[1][2] = n;

    rot_mat[2][0] = 0;
    rot_mat[2][1] = 0;
    rot_mat[2][2] = 1;

    multiply();

    
    
}

void display (void)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    drawTriangle(triangle);
    glColor3f(0,1,0);
    rrotate(0,0);
    drawTriangle(result);
    
    glColor3f(0,0,1);
        m = h * (1-cos(theta)) + k * (sin(theta));
        n = k * (1 - cos(theta)) - h * (sin(theta));
        rrotate(m, n);
        drawTriangle(result);
   
    glFlush();
    
}

int main(int argc, char** argv)
{
    printf("Enter the angle theta: ");
    scanf("%f",&theta);
     printf("Enter the coordinates of x and y for the fixed point : ");
     scanf("%f %f", &h, &k);
    theta = ((3.14 / 180) * theta);


    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

     glutInitWindowSize(720,560);
     glutInitWindowPosition(0,0);
    glutCreateWindow("Rotating Triangle - Aman Kumar (016)");

    glutDisplayFunc(display);
    init();

    glutMainLoop();
}
// 30 - 150 150
// 30 - 100 100
// 60 
