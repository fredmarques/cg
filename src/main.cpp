#include "prefix.h"

#define Updates_Per_Second 24

GLint WINDOW_WIDTH  = 800;
GLint WINDOW_HEIGHT = 800;

void renderScene(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    GLint screen_width = glutGet(GLUT_SCREEN_WIDTH);
    GLint screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
    glutCreateWindow("Aranha");

    // register callbacks
    glutDisplayFunc(renderScene);

    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}
