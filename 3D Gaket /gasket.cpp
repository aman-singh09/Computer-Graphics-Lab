#define GL_SILENCE_DEPRECATION
#include<iostream>
#include<GLUT/glut.h>

int n;
float v[4][3]={{0,0,1},{0,1,-1},{-1,-1,-1},{1,-1,-1}};

void triangle(float a[3],float b[3], float c[3])
{
    glBegin(GL_TRIANGLES);
//    glColor3f(1,0, 0);
        glVertex3f(a[0],a[1],a[2]);
//    glColor3f(0,1, 0);
        glVertex3fv(b);
//    glColor3f(1,0, 1);
        glVertex3fv(c);
    glEnd();
}

void d_triangles(float a[3],float b[3],float c[3],int m)
{
    float v1[3],v2[3],v3[3];
    
    if(m>0)
    {
        for(int i=0;i<3;i++)
        {
            v1[i]=(a[i]+b[i])/2;
            v2[i]=(a[i]+c[i])/2;
            v3[i]=(b[i]+c[i])/2;
        }
        
        d_triangles(a,v1,v2,m-1);
        d_triangles(b,v3, v1,m-1);
        d_triangles(c,v3,v2,m-1);
    }
    else{
        triangle(a,b,c);
    }
}

void tetra()
{
    glColor3f(1,0,0);
    d_triangles(v[0],v[1],v[3],n);
    glColor3f(1,1,0);
    d_triangles(v[1],v[2],v[3],n);
    glColor3f(0,1,0);
    d_triangles(v[0],v[2],v[3],n);
    glColor3f(0,0,1);
    d_triangles(v[0],v[2],v[1],n);
}

void display()
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);
    tetra();
    glFlush();
}
void myinit()
{
    glMatrixMode(GL_PROJECTION);
        glOrtho(-2,2,-2,2,-2,2);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv)
{
    printf("Enter the division details\n:");
    scanf("%d",&n);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("3D Gasket (Fractals) - Aman Kumar(016)");
    glutDisplayFunc(display);
    myinit();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
