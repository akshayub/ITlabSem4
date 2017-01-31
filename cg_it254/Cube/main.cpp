#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

double rotate_y=0;
double rotate_x=0;

void specialKeys(int key, int x, int y) {
    //  Right arrow - increase rotation by 5 degree
    if (key == GLUT_KEY_RIGHT)
      rotate_y += 5;

    //  Left arrow - decrease rotation by 5 degree
    else if (key == GLUT_KEY_LEFT)
      rotate_y -= 5;

    else if (key == GLUT_KEY_UP)
      rotate_x += 5;

    else if (key == GLUT_KEY_DOWN)
      rotate_x -= 5;

    //  Request display update
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Reset transformations
    glLoadIdentity();

    // Rotate when user changes rotate_x and rotate_y
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    /*
    glBegin(GL_POLYGON);
        glColor3f(1,0,0);               //Red
        glVertex3f( -0.5, -0.5, -0.5);  //P1
        glColor3f(0,1,0);               //Green
        glVertex3f( -0.5, 0.5, -0.5);   //P2
        glColor3f(0,0,1);               //Blue
        glVertex3f( 0.5, 0.5, -0.5);    //P3
        glColor3f(1,0,1);               //Purple
        glVertex3f( 0.5, -0.5, -0.5);   //P4
    glEnd();
    */
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cube");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
