#include "prefix.h"
#include "programwindow.h"
#include <assert.h>

unsigned int TickTime = 2;

GLint WINDOW_WIDTH = 800;
GLint WINDOW_HEIGHT = 800;

ProgramWindow *programWindow;

void mouseButtonPressed(int button, int state, int x, int y) {
    ProgramWindow::mouseButtonPressed(button, state, x, y);
}

void loop() {
    ProgramWindow::update();
    glutPostRedisplay();
}

void GLAPIENTRY errorCallback(GLenum /*source*/, GLenum /*type*/, GLuint /*id*/, GLenum severity,
                              GLsizei /*length*/, const GLchar* message, const void* /*userParam*/) {
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        printf("[OpenGL] %x %s", severity, message);
        printf("\n\n");// set breakpoint here
    }
}

int main(int argc, char **argv) {
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // detect current settings
    GLint screen_width = glutGet(GLUT_SCREEN_WIDTH);
    GLint screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
    glutCreateWindow("Aranha");

    glewInit();

    if (glDebugMessageCallback) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(errorCallback, nullptr);
        GLuint unusedID = 0;
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedID, true);
    } else {
        assert(!"proper error reporting is essential!");
    }

    programWindow = new ProgramWindow(true);
    glutMouseFunc(mouseButtonPressed);
    glutDisplayFunc(ProgramWindow::render);
    glutIdleFunc(loop);
    glutMainLoop();

    return EXIT_SUCCESS;
}