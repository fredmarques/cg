#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "prefix.h"
using namespace std;

class ProgramWindow {

    private:
        bool _running;
        GLfloat _height;
        GLfloat _width;

        void setupGL();

    public:
        ProgramWindow(bool running);
        void setRunning(bool newRunning);
        bool getRunning();
        static void render();
        static void update();
        static void mouseButtonPressed(int button, int state, int x, int y);
        static void keyboardButtonPressed(unsigned char key, int x, int y);
        static void reshapeCallback(int w, int h);
};

#endif