#include "prefix.h"
#include "programwindow.h"
#include "float3.h"
#include "math.h"


using namespace std;
GLint width = 800;
GLint height = 800;

struct Spider {
    struct {
        float3 curr = {1.0f, 1.0f, 1.0f};
        float3 target = {1.0f, 1.0f, 1.0f};
        int flag = 0;
    }pos;
    float3 scale = {1, 1, 1};
    struct {
        float curr = 0;
        float target = 0;
        float dist = 0;
        bool dir = true; // true -> C.C.W | false -> C.W (Clock.Wise)
        bool roting = false;
        float offset = 0;
    } rot;
};

struct Transform
{
    float3 pos = {0, 0, 0};
    float3 scale = {0.01, 0.01, 0.01};
    struct {
        float angleRad = PI/3;
        const float3 vec = {1, 1, 1};
    } rot;
};

Spider spider;

Transform circleTransform, circle2Transform, leg1Part1, leg1Part2, leg2Part1, leg2Part2, 
          leg3Part1, leg3Part2, leg4Part1, leg4Part2, leg5Part1, leg5Part2, leg6Part1, leg6Part2, 
          leg7Part1, leg7Part2, leg8Part1, leg8Part2;

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
    // gluOrtho2D(0, _width, 0, _height);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

/*void moveTo(){
     while(spider.pos.curr.x != spider.pos.target.x or spider.pos.curr.y != 400.0f spider.pos.target.y){
           spider.pos.curr += float3(0.0f,0.01f,0.0f);
           spider.pos.curr += float3(0.01f,0.0f,0.0f);
     }
}*/

void ProgramWindow::setRunning(bool newRunning) {
    _running = newRunning;
}

bool ProgramWindow::getRunning() {
    return _running;
}

void ProgramWindow::mouseButtonPressed(int button, int state, int x, int y) {
    cout << "clique do mouse:" << endl;
    cout << "button: " << button << "\nstate: " << state << "\nx:" << x << "\ny:" << y << endl;
    cout << "angle: " << circleTransform.rot.angleRad;
    cout << "------------" << endl;
    spider.pos.target = {x, y, 0};
    spider.pos.flag = state;
}

void ProgramWindow::keyboardButtonPressed(unsigned char key, int x, int y)
{
    printf("[keyboard]\n");
    // post = angulo * cosf
    float3 step = {10.0, 10.0, 0};
    float3 angle = {0.0, 0.0, 0.0};

    switch (key)
    {
    case 'w':
        angle = float3(-sinf(spider.rot.curr), cosf(spider.rot.curr), 1);
        printf("[keyboard] %c %f %f\n", key, angle.x, angle.y);
        spider.pos.curr = spider.pos.curr + (step * angle);
        printf("rot: %f ", cosf(spider.rot.curr));
        break;
    case 's':
        angle = float3(-sinf(spider.rot.curr), cosf(spider.rot.curr), 1);
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
}

void transform(const Transform& transform) {
    // transform
    glTranslatef(transform.pos.x, transform.pos.y, transform.pos.z);
    glRotatef(transform.rot.angleRad * RAD2DEG, transform.rot.vec.x, transform.rot.vec.y, transform.rot.vec.z);
    glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
}

void ProgramWindow::update() {
    int msecs = glutGet(GLUT_ELAPSED_TIME);
    float time = 1e-3f * msecs;

    //movimenta a aranha
    
    if (spider.pos.flag == 1 and spider.pos.curr.x != spider.pos.target.x and circleTransform.rot.angleRad >= 0 and circleTransform.rot.angleRad <=PI/2.0f){
         spider.pos.curr -= float3(0.01f,0.0f,0.0f);
    }

    if( spider.pos.flag == 1 and spider.pos.curr.y != spider.pos.target.y and circleTransform.rot.angleRad >= 0 and circleTransform.rot.angleRad <=PI/2.0f){
         spider.pos.curr += float3(0.0f,0.01f,0.0f);
    }
    if (spider.pos.flag == 1 and spider.pos.curr.x != spider.pos.target.x and circleTransform.rot.angleRad > PI/2.0f and circleTransform.rot.angleRad <=PI){
         spider.pos.curr -= float3(0.01f,0.0f,0.0f);
    }

    if( spider.pos.flag == 1 and spider.pos.curr.y != spider.pos.target.y and circleTransform.rot.angleRad > PI/2.0f and circleTransform.rot.angleRad <=PI){
         spider.pos.curr -= float3(0.0f,0.01f,0.0f);
    }

//works until here

    if (spider.pos.flag == 1 and spider.pos.curr.x != spider.pos.target.x and circleTransform.rot.angleRad > -PI and circleTransform.rot.angleRad < -PI/2.0f){
         spider.pos.curr += float3(0.01f,0.0f,0.0f);
    }

    if( spider.pos.flag == 1 and spider.pos.curr.y != spider.pos.target.y and circleTransform.rot.angleRad >= -PI and circleTransform.rot.angleRad < -PI/2.0f){
         spider.pos.curr -= float3(0.0f,0.01f,0.0f);
    }

//works

    if (spider.pos.flag == 1 and spider.pos.curr.x != spider.pos.target.x and circleTransform.rot.angleRad > -PI/2.0f and circleTransform.rot.angleRad <0){
         spider.pos.curr += float3(0.01f,0.0f,0.0f);
    }

    if( spider.pos.flag == 1 and spider.pos.curr.y != spider.pos.target.y and circleTransform.rot.angleRad > - PI/2.0f and circleTransform.rot.angleRad < 0){
         spider.pos.curr += float3(0.0f,0.01f,0.0f);
    }

    // find angle to move to click
    float3 delta = spider.pos.curr - spider.pos.target;
    float angle = atan2f(delta.x, delta.y);
    // printf(">> angle: %f\n", angle);
    spider.rot.target = angle;

    float deltaAngle = spider.rot.curr - spider.rot.target;
    spider.rot.dir = deltaAngle < 0;
    // spider.rot.dir = spider.rot.target < 0 && spider.rot.curr < 0 ? !spider.rot.dir : spider.rot.dir;

    if (abs(deltaAngle) > 3.2) {
        spider.rot.dist = abs(deltaAngle) - 3.2;
        spider.rot.dir = !spider.rot.dir;
    } else {
        spider.rot.dist = abs(deltaAngle);
    }
/*
    printf("------------------\n");
    printf("target: %f\n", spider.rot.target);
    printf("curr: %f\n", spider.rot.curr);
    printf("dist: %f\n", spider.rot.dist);
    printf("direction: %f\n", spider.rot.dir);
    printf("flag: %f\n", spider.pos.flag);
    printf("flag: %f\n", spider.pos.target);
    printf("flag: %f\n", spider.pos.curr);
    printf("------------------\n");
*/
    if(spider.rot.dist > 0.1) {
        float da = abs(spider.rot.target) / time * 0.05;
        // if angle goes beyond limits, change singal and take the complementar angle
        if(abs(spider.rot.curr) > 3.2) {
            spider.rot.curr = 3.2 - (spider.rot.curr - 3.2);
            spider.rot.dir = !spider.rot.dir;
        }
    
        if (spider.rot.dir) {
            spider.rot.curr += da;
        }else {
            spider.rot.curr -= da;
        }
    }

    circleTransform.pos = spider.pos.curr;
    circleTransform.rot.angleRad = spider.rot.curr;
    

    // Transformation
    
/*
    leg3Part1.rot.angleRad = PI/8; // Same

    leg3Part2.pos = float3(-195, 0, 0);
    leg3Part2.rot.angleRad = - PI / 3; // Same

    leg3Part1.rot.angleRad *= -1 * sin01(time * 2); // multiply -1


   /* 
    leg2Part1.pos = float3(0, 0, 0);
    leg2Part1.rot.angleRad = PI / 6;

    leg2Part2.pos = float3(-195, 0, 0);
    leg2Part2.rot.angleRad =  PI / 6;

    leg3Part1.pos = float3(0, 0, 0);
    leg3Part1.rot.angleRad = PI / 6;

    leg3Part2.pos = float3(195, 0, 0);
    leg3Part2.rot.angleRad = - PI / 6;



    leg3Part1.rot.angleRad *= sin01(time * 3);
*/
    // Movimentação
    
    //leg1Part1.rot.angleRad = PI/4 * sin01(time * 2);


    leg1Part1.pos = float3(60, 60, 0);
    leg1Part2.pos = float3(193, 0, 0);
    leg1Part2.rot.angleRad = - PI / 3;
    leg1Part1.rot.angleRad = (4*PI)/8;
    leg1Part1.rot.angleRad = PI/8 * (sin01(time * 5) + (4*PI)/8);

    leg2Part1.pos = float3(70, 20, 0);
    leg2Part2.pos = float3(153, 0, 0);
    leg2Part2.rot.angleRad = - PI / 3;
    leg2Part1.rot.angleRad = (2*PI)/8;
    leg2Part1.rot.angleRad = PI/8 * (sin01(time * 4) + (2*PI)/8);

    leg3Part1.pos = float3(80, -10, 0);
    leg3Part2.pos = float3(113, 0, 0);
    leg3Part2.rot.angleRad = - PI / 3;
    leg3Part1.rot.angleRad = PI/8;
    leg3Part1.rot.angleRad = PI/8 * (sin01(time * 3) + PI/8);

    leg4Part1.pos = float3(70, -40, 0);
    leg4Part2.pos = float3(93, 0, 0);
    leg4Part2.rot.angleRad = - PI / 4;
    leg4Part1.rot.angleRad = -(2*PI)/8;
    leg4Part1.rot.angleRad = PI/8 * (sin01(time * 4) - (2*PI)/8);


    leg5Part1.pos = float3(-60, 60, 0);
    leg5Part2.pos = float3(-193, 0, 0);
    leg5Part2.rot.angleRad = PI / 3;
    leg5Part1.rot.angleRad = (-4*PI)/8;
    leg5Part1.rot.angleRad = PI/8 * (sin01(time * 5) + (-4*PI)/8);

    leg6Part1.pos = float3(-70, 20, 0);
    leg6Part2.pos = float3(-153, 0, 0);
    leg6Part2.rot.angleRad = PI / 3;
    leg6Part1.rot.angleRad = (-2*PI)/8;
    leg6Part1.rot.angleRad = PI/8 * (sin01(time * 4) + (-2*PI)/8);

    leg7Part1.pos = float3(-80, -10, 0);
    leg7Part2.pos = float3(-113, 0, 0);
    leg7Part2.rot.angleRad = PI / 3;
    leg7Part1.rot.angleRad = -PI/8;
    leg7Part1.rot.angleRad = PI/8 * (sin01(time * 3) - PI/8);

    leg8Part1.pos = float3(-70, -40, 0);
    leg8Part2.pos = float3(-93, 0, 0);
    leg8Part2.rot.angleRad = PI / 4;
    leg8Part1.rot.angleRad = (-2*PI)/8;
    leg8Part1.rot.angleRad = PI/8 * (sin01(time * 4) - (-2*PI)/8);


    circle2Transform.pos = float3(0, -220, 0);
}

void draw() {
    glColor3f(0,0,0);

    transform(circleTransform);
    drawCircle(float3(0), float3(100, 100, 100));

    glPushMatrix();
        transform(leg1Part1);
        drawQuad(float3(0), float3(200, 15, 150));

        transform(leg1Part2);
        drawQuad(float3(0, 0, 0), float3(100, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(leg2Part1);
        drawQuad(float3(0, 0, 0), float3(160, 15, 15));

        transform(leg2Part2);
        drawQuad(float3(0, 0, 0), float3(80, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(leg3Part1);
        drawQuad(float3(0, 0, 0), float3(120, 15, 15));

        transform(leg3Part2);
        drawQuad(float3(0, 0, 0), float3(60, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(leg4Part1);
        drawQuad(float3(0, 0, 0), float3(100, 15, 15));

        transform(leg4Part2);
        drawQuad(float3(0, 0, 0), float3(140, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(leg5Part1);
        drawQuad(float3(0, 0, 0), float3(-200, 15, 15));

        transform(leg5Part2);
        drawQuad(float3(0, 0, 0), float3(-100, 15, 15));
    glPopMatrix();


    glPushMatrix();
        transform(leg6Part1);
        drawQuad(float3(0, 0, 0), float3(-160, 15, 15));

        transform(leg6Part2);
        drawQuad(float3(0, 0, 0), float3(-80, 15, 15));
    glPopMatrix();


    glPushMatrix();
        transform(leg7Part1);
        drawQuad(float3(0, 0, 0), float3(-120, 15, 15));

        transform(leg7Part2);
        drawQuad(float3(0, 0, 0), float3(-60, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(leg8Part1);
        drawQuad(float3(0, 0, 0), float3(-100, 15, 15));

        transform(leg8Part2);
        drawQuad(float3(0, 0, 0), float3(-140, 15, 15));
    glPopMatrix();

    glPushMatrix();
        transform(circle2Transform);
        drawCircle(float3(0), float3(120, 160, 160));
    glPopMatrix();
}

void ProgramWindow::render() {

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);

    glLoadIdentity();
	gluLookAt(6.0, 2.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0,0,0);

	glViewport(0, 0, width, height);
    draw();

	glViewport(0, 0, width/2, height/2);
     glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 100.0f, 100.0f, -100.0f);
      glVertex3f(-100.0f, 100.0f, -100.0f);
      glVertex3f(-100.0f, 100.0f,  100.0f);
      glVertex3f( 100.0f, 100.0f,  100.0f);
 
      // Bottom face (y = -100.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 100.0f, -100.0f,  100.0f);
      glVertex3f(-100.0f, -100.0f,  100.0f);
      glVertex3f(-100.0f, -100.0f, -100.0f);
      glVertex3f( 100.0f, -100.0f, -100.0f);
 
      // Front face  (z = 100.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 100.0f,  100.0f, 100.0f);
      glVertex3f(-100.0f,  100.0f, 100.0f);
      glVertex3f(-100.0f, -100.0f, 100.0f);
      glVertex3f( 100.0f, -100.0f, 100.0f);
 
      // Back face (z = -100.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 100.0f, -100.0f, -100.0f);
      glVertex3f(-100.0f, -100.0f, -100.0f);
      glVertex3f(-100.0f,  100.0f, -100.0f);
      glVertex3f( 100.0f,  100.0f, -100.0f);
 
      // Left face (x = -100.0f)
      glColor3f(0.0f, 0.0f, 100.0f);     // Blue
      glVertex3f(-100.0f,  100.0f,  100.0f);
      glVertex3f(-100.0f,  100.0f, -100.0f);
      glVertex3f(-100.0f, -100.0f, -100.0f);
      glVertex3f(-100.0f, -100.0f,  100.0f);
 
      // Right face (x = 100.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(100.0f,  100.0f, -100.0f);
      glVertex3f(100.0f,  100.0f,  100.0f);
      glVertex3f(100.0f, -100.0f,  100.0f);
      glVertex3f(100.0f, -100.0f, -100.0f);
    glEnd();  // End of drawing color-cube

    glutSwapBuffers();
}

void ProgramWindow::reshapeCallback(int w, int h)
{
	/** Atualiza os valores da janela */
	width = w;
	height = h;
	/** Define o volume de vista */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat) width/(GLfloat) height, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}
