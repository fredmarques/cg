#include "prefix.h"
#include "programwindow.h"

using namespace std;

typedef struct {
    GLfloat positionCoordinates[3];
    GLfloat textureCoordinates[2];
} VertexData;


ProgramWindow::ProgramWindow(bool running): _running(running), _height(800), _width(800), _vertexBufferID(0) {
    setupGL();
}

void ProgramWindow::setupGL() {
    glClearColor(0,0,0,0);
    glViewport(0,0,_width,_height);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,_width, 0, _height);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();
}

void ProgramWindow::setRunning(bool newRunning) {
    _running = newRunning;	
}

bool ProgramWindow::getRunning() {
    return _running;
}

void ProgramWindow::mouseButtonPressed(int button, int state, int x, int y) {
    cout << "clique do mouse:" << endl;
    cout << "button: " << button << "\nstate: " << state << "\nx:" << x << "\ny:" << y << endl;
    cout << "------------" << endl;
}

void ProgramWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
    glEnd();
    glutSwapBuffers();
}

void ProgramWindow::update() {
}
