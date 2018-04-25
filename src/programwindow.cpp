#include "prefix.h"
#include "programwindow.h"
#include "float3.h"


using namespace std;

struct VertexData {
    float3 pos;
// 	float2 uv;
};

struct Transform {
    float3 pos = {0, 0, 0};
    float3 scale = {1, 1, 1};
    struct {
        float angleRad = 0;
        const float3 vec = {0, 0, 1};
    } rot;
};

Transform circleTransform, quadTransform, quadTransform2, quadTransform3, quadTransform4, 
          quadTransform5, quadTransform6, quadTransform7, quadTransform8;

void drawCircle(float3 center, float3 radius, int segments = 64) {
    glBegin(GL_TRIANGLES);
    GLfloat step = TAL / segments;
    for (int i = 0; i < segments; i++) {
        GLfloat angle1 = i * step;
        GLfloat angle2 = (i + 1) * step;
        
        float3 v2 = center + radius * float3(cosf(angle2), sinf(angle2), 0);
        float3 v3 = center + radius * float3(cosf(angle1), sinf(angle1), 0);

        glVertex3f(center[0], center[1], center[2]);
        glVertex3f(v2[0], v2[1], v2[2]);
        glVertex3f(v3[0], v3[1], v3[2]);
    }
    glEnd();
}

void drawQuad(float3 pos, float3 dim) {

    float3 p1 = float3(pos.x, pos.y + dim.y / 2.0, 0);
    float3 p2 = float3(pos.x + dim.x, pos.y + dim.y / 2.0, 0);
    float3 p3 = float3(pos.x + dim.x, pos.y - dim.y / 2.0, 0);
    float3 p4 = float3(pos.x, pos.y - dim.y / 2.0, 0);

    glBegin(GL_QUADS);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
}

ProgramWindow::ProgramWindow(bool running) : _running(running), _height(800), _width(800) {
    setupGL();
}

void ProgramWindow::setupGL() {
    //////////////////////////////////////////////////////////////////////////
    // Create things to look at

    // OH LOOK A CIRCLE
    

    // OH LOOK A QUAD :D
    // VertexData quadVerts[6] = {
    //     {{-.5f, +.5f, 0.f}},
    //     {{-.5f, -.5f, 0.f}},
    //     {{+.5f, -.5f, 0.f}},

    //     {{-.5f, +.5f, 0.f}},
    //     {{+.5f, -.5f, 0.f}},
    //     {{+.5f, +.5f, 0.f}},
    // };

    // ajusting view
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, _width, 0, _height);

    glMatrixMode(GL_MODELVIEW);
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

void transform(const Transform& transform) {
    // transform
    glTranslatef(transform.pos.x, transform.pos.y, transform.pos.z);
    glRotatef(transform.rot.angleRad * RAD2DEG, transform.rot.vec.x, transform.rot.vec.y, transform.rot.vec.z);
    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
}

void ProgramWindow::render() {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glColor3f(0,0,0);

    transform(circleTransform);
    drawCircle(float3(0), float3(100, 200, 1));

    glPushMatrix();
        transform(quadTransform);
        drawQuad(float3(100, 0, 0), float3(100, 40, 0));

        transform(quadTransform2);
        drawQuad(float3(0, 0, 0), float3(100, 40, 0));
    glPopMatrix();

    glPushMatrix();
        transform(quadTransform3);
        drawQuad(float3(-100, 0, 0), float3(-100, -40, 0));

        transform(quadTransform4);
        drawQuad(float3(0, 0, 0), float3(-100, -40, 0));
    glPopMatrix();

    glPushMatrix();
        transform(quadTransform);
        drawQuad(float3(100, 50, 0), float3(100, 40, 0));

        transform(quadTransform2);
        drawQuad(float3(-20, 45, 0), float3(100, 40, 0));
    glPopMatrix();

    glutSwapBuffers();
}


void ProgramWindow::update() {
    int msecs = glutGet(GLUT_ELAPSED_TIME);
    float time = 1e-3f * msecs;
    circleTransform.pos = float3(400, 400, 0);
    
    quadTransform.pos = float3(0, 0, 0);
    quadTransform.rot.angleRad = PI / 6 * sin01(time * 3);

    quadTransform2.pos = float3(180, 0, 0);
    quadTransform2.rot.angleRad = - PI / 8;
    
    quadTransform3.pos = float3(0, 0, 0);
    quadTransform3.rot.angleRad = PI / 6 * (-1*sin01(time * 3));

    quadTransform4.pos = float3(-180, 0, 0);
    quadTransform4.rot.angleRad =  PI / 8;

    quadTransform5.pos = float3(0, 0, 0);
    quadTransform5.rot.angleRad = PI / 6 * sin01(time * 3);

    quadTransform6.pos = float3(180, 0, 0);
    quadTransform6.rot.angleRad = - PI / 8;
    
    quadTransform7.pos = float3(0, 0, 0);
    quadTransform7.rot.angleRad = PI / 6 * (-1*sin01(time * 3));

    quadTransform8.pos = float3(-180, 0, 0);
    quadTransform8.rot.angleRad =  PI / 8;
}
