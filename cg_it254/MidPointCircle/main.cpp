#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include<stdlib.h>

void setPixel(GLint x,GLint y){
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void Circle(){

  int xCenter=100,yCenter=100,r=50;
  int x=0,y=r;
  int p = 3/2 - r;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 0, 0, 0);
  while(x<=y){
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter+y,yCenter+x);
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter+y,yCenter-x);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter-y,yCenter-x);
    setPixel(xCenter+x,yCenter-y);
    setPixel(xCenter-y,yCenter+x);

    if (p<0)
        p += (2*x)+3;
    else {
        p += (2*(x-y))+5;
        y -= 1;
    }
    x++;
  }
  glFlush();
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    //glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham Circle");
    glClearColor(1.0,1.0,1.0,0.0);
    //glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,200.0);
    glutDisplayFunc(Circle);
    glutMainLoop();
    return 0;
}
