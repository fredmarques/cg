#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "prefix.h"
using namespace std;

class ProgramWindow {

    private:
        bool _running;
        GLfloat _height;
        GLfloat _width;
        GLuint _vertexBufferID;
        GLuint _textureBufferID;
        void setupGL();

    public:
        ProgramWindow(bool running);
        void setRunning(bool newRunning);
        bool getRunning();
        static void render();
        static void update();
};

#endif