#include "prefix.h"
#include "programwindow.h"
#include "float3.h"


using namespace std;

struct Spider {
    struct {
        float3 curr = {400, 400, 0};
        float3 target = {400, 400, 0};
        float3 dir = {0,0,0};
        bool moving = false;
    }pos;
    float3 scale = {1, 1, 1};
    struct {
        float curr = 0.0;
        float target = 0.0;
        float prev = 0.0;
        float dist = 0.0;
        float angle = 0.0;
        bool dir = true; // true -> C.C.W | false -> C.W (Clock.Wise)
        bool rotating = false;
    } rot;
};

struct Transform
{
    float3 pos = {0, 0, 0};
    float3 scale = {1, 1, 1};
    struct {
        float angleRad = 0;
        const float3 vec = {0, 0, 1};
    } rot;
};

Spider spider;

Transform circleTransform, quadTransform, quadTransform2, quadTransform3, quadTransform4, 
          quadTransform5, quadTransform6, quadTransform7, quadTransform8, boxTransform;

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

// void ProgramWindow::mouseButtonPressed(int button, int state, int x, int y) {
//     spider.pos.target = {x, y, 0};
//     // printf(">>target: %d, %d\n", x, y);
//     cout <<"target " << x << ", " << y << ", " << state << endl;
//     printf("curr: %f, %f\n", spider.pos.curr.x, spider.pos.curr.y);
//     spider.pos.dir = spider.pos.target - spider.pos.curr ;
//     printf("dir: %f, %f\n", spider.pos.dir.x, spider.pos.dir.y);

//     spider.pos.dir /= sqrtf32(powf32(spider.pos.dir.x, 2) + powf32(spider.pos.dir.y, 2));
//     spider.pos.moving = false;

//     float3 delta = spider.pos.curr - spider.pos.target;
//     float angle = atan2f(delta.x, delta.y);
//     spider.rot.target = angle;

//     // if angle goes beyond limits, change singal and take the complementar angle
//     float d = (abs(spider.rot.curr) - 3.2);
//     if(spider.rot.curr > 3.2) {
//         spider.rot.curr = -(3.2 - d);
//     } else if (spider.rot.curr < - 3.2) {
//         spider.rot.curr = (3.2 - d);
//     }
// }
void ProgramWindow::keyboardButtonPressed(unsigned char key, int x, int y) {
    printf("[keyboard]\n");
    // post = angulo * cosf
    float3 step = {10.0, 10.0, 0};
    float3 angle = {0.0, 0.0, 0.0};

    switch (key) {
    case 'w':
        angle = float3(-sinf(spider.rot.curr), cosf(spider.rot.curr) , 1);
        printf("[keyboard] %c %f %f\n", key, angle.x, angle.y);
        spider.pos.curr = spider.pos.curr + (step * angle);
        printf("rot: %f ", cosf(spider.rot.curr));
        break;
    case 's':
        angle = float3(-sinf(spider.rot.curr), cosf(spider.rot.curr) , 1);
        printf("[keyboard] %c %f %f\n", key, angle.x, angle.y);
        spider.pos.curr = spider.pos.curr - (step * angle);
        printf("rot: %f ", cosf(spider.rot.curr));
        break;
        break;
    case 'a':
        printf("[keyboard] %c %d %d\n", key, x, y);
        spider.rot.curr += (PI / 18);
        printf("rot: %f ", cosf(spider.rot.curr));
        break;
    case 'd':
        printf("[keyboard] %c %d %d\n", key, x, y);
        spider.rot.curr -= (PI / 18);
        printf("rot: %f ", cosf(spider.rot.curr));
        break;
    }
    // spider.pos.target = {x, y, 0};
    // // printf(">>target: %d, %d\n", x, y);
    // cout <<"target " << x << ", " << y << ", " << state << endl;
    // printf("curr: %f, %f\n", spider.pos.curr.x, spider.pos.curr.y);
    // spider.pos.dir = spider.pos.target - spider.pos.curr ;
    // printf("dir: %f, %f\n", spider.pos.dir.x, spider.pos.dir.y);

    // spider.pos.dir /= sqrtf32(powf32(spider.pos.dir.x, 2) + powf32(spider.pos.dir.y, 2));
    // spider.pos.moving = false;

    // float3 delta = spider.pos.curr - spider.pos.target;
    // float angle = atan2f(delta.x, delta.y);
    // spider.rot.target = angle;

    // // if angle goes beyond limits, change singal and take the complementar angle
    // float d = (abs(spider.rot.curr) - 3.2);
    // if(spider.rot.curr > 3.2) {
    //     spider.rot.curr = -(3.2 - d);
    // } else if (spider.rot.curr < - 3.2) {
    //     spider.rot.curr = (3.2 - d);
    // }
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

    // if(spider.rot.prev != spider.rot.target) {
    //     spider.rot.prev = spider.rot.target;
    
    //     float deltaAngle = spider.rot.curr - spider.rot.target;

    //     // spider.rot.dist = abs(deltaAngle);
    //     spider.rot.dir = deltaAngle < 0;
    //     // if complementar angle, use the small one
    //     if (abs(deltaAngle) > 3.2) {
    //         // taking smallest angular space
    //         spider.rot.dist = abs(6.4 - abs(deltaAngle) - 0.11);
    //         // change direction to move through smallest angle
    //         spider.rot.dir = !spider.rot.dir;
    //     } else {
    //         // taking regular angular space
    //         spider.rot.dist = abs(deltaAngle);
    //     }
    //     spider.rot.rotating = true;
    // }

    // float da = 3.2 / PI / 130;
    // float da = 3.2 / PI / 80;
    // if(spider.rot.dist > da && spider.rot.rotating) {

    //     if (spider.rot.dir) {
    //         spider.rot.curr += da;
    //     } else {
    //         spider.rot.curr -= da;
    //     }
    //     spider.rot.dist -= da;
    // } else if(spider.rot.rotating){
    //     spider.rot.dist = 0;
    //     spider.rot.rotating = false;
    //     spider.rot.curr = spider.rot.target;
    //     spider.pos.moving = true;

        // printf("------------------\n");
        // printf("target: %f\n", spider.rot.target);
        // printf("curr: %f\n", spider.rot.curr);
        // printf("prev: %f\n", spider.rot.prev);
        // printf("dist: %f\n", spider.rot.dist);
        // printf("direction: %d\n", spider.rot.dir);
        // printf("------------------\n");
    // }

    // circleTransform.pos = spider.pos.curr;
    // float3 delta = spider.pos.target - spider.pos.curr;
    // printf("delta: %f, %f\n", delta.x, delta.y);

    // if (spider.pos.moving && abs(delta.x) > 0.01 && abs(delta.y) > 0.01) {
    //     // printf("dir: %f, %f\n", spider.pos.dir.x, spider.pos.dir.y);
    //     spider.pos.curr += spider.pos.dir;
    //     // printf("curr: %f, %f\n", spider.pos.curr.x, spider.pos.curr.y);
    //     // printf("target: %f, %f\n", spider.pos.target.x, spider.pos.target.y);
    // } else if(spider.pos.moving) {
    //     printf("stop!\n");
    //     spider.pos.curr = spider.pos.target;
    //     spider.pos.moving = false;
    // }

    circleTransform.rot.angleRad = spider.rot.curr;
    circleTransform.pos = spider.pos.curr;
    // circleTransform.scale = float3(1 + sin01(time * 3) * 0.1,1+ sin01(time * 3) * 0.1,1);
    
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

    // quadTransform7.pos = float3(0, 0, 0);
    // quadTransform7.rot.angleRad = PI / 6 * (-1*sin01(time * 3));

    // quadTransform8.pos = float3(-180, 0, 0);
    // quadTransform8.rot.angleRad =  PI / 8;
}
