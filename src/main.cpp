#include "prefix.h"
#include "programwindow.h"

unsigned int Updates_Per_Second = 24;

GLint WINDOW_WIDTH  = 800;
GLint WINDOW_HEIGHT = 800;

ProgramWindow *programWindow;
void Timer(int iUnused)
{
    glutTimerFunc(Updates_Per_Second, Timer, 0);
    glutPostRedisplay();
    ProgramWindow::update();
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

    programWindow = new ProgramWindow(true);
    // calls render to avoid update been called before render
    ProgramWindow::render();
    glutDisplayFunc(ProgramWindow::render);
    Timer(0);
    glutMainLoop();

    return 1;
}
