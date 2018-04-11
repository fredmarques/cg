#include "prefix.h"
#include "programWindow.h"

using namespace std;

typedef struct {
    GLfloat positionCoordinates[3];
    GLfloat textureCoordinates[2];
} VertexData;


ProgramWindow::ProgramWindow(bool running): _running(running), _height(600), _width(600), _vertexBufferID(0) {
    setupGL();
}

void ProgramWindow::setupGL() {
    // glClearColor(1.0f,1.0f,1.0f,1.0f);
    // glViewport(0,0,_width,_height);
    // glMatrixMode(GL_PROJECTION);
    // gluOrtho2D(0,_width, 0, _height);
    // glMatrixMode(GL_MODELVIEW);	
    // glEnable(GL_TEXTURE_2D);
}

void ProgramWindow::setRunning(bool newRunning) {
    _running = newRunning;	
}

bool ProgramWindow::getRunning() {
    return _running;
}

void ProgramWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glutSwapBuffers();
}

void ProgramWindow::update() {
}
