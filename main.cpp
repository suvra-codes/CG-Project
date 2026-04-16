#include <GL/glut.h>
#include <math.h>

// -------- VARIABLES --------

float cloudX1 = -300;
float cloudX2 = 100;


int is3D = 0;

float angleX = 0;
float angleY = 0;

float crossDelay = 0;
int startCross = 0;

int crossed = 0;
float human1Y = 70;
float human2Y = 70;

int cross = 0;

float carX = -400;
float car2X = -600;
float car3X = -800;

float wheelRot = 0;
int signal = 1; // 1=green, 0=red

// -------- MIDPOINT CIRCLE --------
void drawCircle(int xc,int yc,int r)
{
    int x=0,y=r,p=1-r;
    glBegin(GL_POINTS);
    while(x<=y){
        glVertex2i(xc+x,yc+y); glVertex2i(xc-x,yc+y);
        glVertex2i(xc+x,yc-y); glVertex2i(xc-x,yc-y);
        glVertex2i(xc+y,yc+x); glVertex2i(xc-y,yc+x);
        glVertex2i(xc+y,yc-x); glVertex2i(xc-y,yc-x);
        x++;
        if(p<0) p+=2*x+1;
        else{ y--; p+=2*(x-y)+1; }
    }
    glEnd();
}

// -------- FILLED CIRCLE --------
void drawFilledCircle(float cx,float cy,float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);
    for(int i=0;i<=100;i++)
    {
        float a = 2*3.1416*i/100;
        glVertex2f(cx+cos(a)*r, cy+sin(a)*r);
    }
    glEnd();
}

// -------- TRAFFIC LIGHT --------
void drawSignal()
{
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0,60);
    glVertex2f(10,60);
    glVertex2f(10,150);
    glVertex2f(0,150);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-10,150);
    glVertex2f(30,150);
    glVertex2f(30,230);
    glVertex2f(-10,230);
    glEnd();

    if(signal==0) glColor3f(1,0,0);
    else glColor3f(0.3,0,0);
    drawFilledCircle(10,210,10);

    if(signal==1) glColor3f(0,1,0);
    else glColor3f(0,0.3,0);
    drawFilledCircle(10,170,10);
}

// -------- ROAD --------
void drawRoad()
{
    // grass (ground)
    glColor3f(0.4,0.7,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(-500,-300);
    glVertex2f(500,-300);
    glVertex2f(500,100);
    glVertex2f(-500,100);
    glEnd();

    // road
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(-500,-60);
    glVertex2f(500,-60);
    glVertex2f(500,60);
    glVertex2f(-500,60);
    glEnd();

    // borders
    glColor3f(0.8,0.8,0.8);
    glBegin(GL_POLYGON);
    glVertex2f(-500,60); glVertex2f(500,60);
    glVertex2f(500,70); glVertex2f(-500,70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-500,-60); glVertex2f(500,-60);
    glVertex2f(500,-70); glVertex2f(-500,-70);
    glEnd();

    // divider
    glColor3f(1,1,1);
    for(int i=-400;i<400;i+=50)
    {
        glBegin(GL_POLYGON);
        glVertex2f(i,-5);
        glVertex2f(i+20,-5);
        glVertex2f(i+20,5);
        glVertex2f(i,5);
        glEnd();
    }

    // zebra
    for(int i=-40;i<=40;i+=10)
    {
        glBegin(GL_POLYGON);
        glVertex2f(-50,i);
        glVertex2f(50,i);
        glVertex2f(50,i+5);
        glVertex2f(-50,i+5);
        glEnd();
    }
}

// -------- CAR --------
void drawCar(float x,float y,float r,float g,float b)
{
    glPushMatrix();
    glTranslatef(x,y,0);

    glScalef(1.05,1.05,1);

    glColor4f(0,0,0,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-50,-15);
    glVertex2f(50,-15);
    glVertex2f(50,-20);
    glVertex2f(-50,-20);
    glEnd();

    glColor3f(r,g,b);
    glBegin(GL_POLYGON);
    glVertex2f(-40,10);
    glVertex2f(40,10);
    glVertex2f(30,30);
    glVertex2f(-30,30);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-50,-10);
    glVertex2f(50,-10);
    glVertex2f(50,10);
    glVertex2f(-50,10);
    glEnd();

    glColor3f(0.6,0.8,1);
    glBegin(GL_POLYGON);
    glVertex2f(-20,15);
    glVertex2f(20,15);
    glVertex2f(15,28);
    glVertex2f(-15,28);
    glEnd();

    glPushMatrix();
    glTranslatef(-25,-10,0);
    glRotatef(wheelRot,0,0,1);
    glColor3f(0,0,0);
    drawFilledCircle(0,0,10);
    glColor3f(1,1,1);
    drawCircle(0,0,10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25,-10,0);
    glRotatef(wheelRot,0,0,1);
    glColor3f(0,0,0);
    drawFilledCircle(0,0,10);
    glColor3f(1,1,1);
    drawCircle(0,0,10);
    glPopMatrix();

    glPopMatrix();
}

// -------- BIKE --------
void drawBike(float x,float y)
{
    glPushMatrix();
    glTranslatef(x,y,0);

    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-20,5);
    glVertex2f(20,5);
    glVertex2f(10,15);
    glVertex2f(-10,15);
    glEnd();

    glPushMatrix();
    glTranslatef(-15,-5,0);
    glRotatef(wheelRot,0,0,1);
    glColor3f(0,0,0);
    drawFilledCircle(0,0,8);
    glColor3f(1,1,1);
    drawCircle(0,0,8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15,-5,0);
    glRotatef(wheelRot,0,0,1);
    glColor3f(0,0,0);
    drawFilledCircle(0,0,8);
    glColor3f(1,1,1);
    drawCircle(0,0,8);
    glPopMatrix();

    glPopMatrix();
}

// -------- TREE --------
void drawTree(float x,float y)
{
    glColor3f(0.4,0.25,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(x,y);
    glVertex2f(x+10,y);
    glVertex2f(x+10,y+40);
    glVertex2f(x,y+40);
    glEnd();

    glColor3f(0,0.6,0);
    drawFilledCircle(x+5,y+55,20);
    drawFilledCircle(x-5,y+50,15);
    drawFilledCircle(x+15,y+50,15);
}

// -------- Far TREE --------
void drawFarTree(float x,float y)
{
    glPushMatrix();

    glTranslatef(x,y,0);
    glScalef(0.5,0.5,1);

    glColor3f(0.5,0.35,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(8,0);
    glVertex2f(8,30);
    glVertex2f(0,30);
    glEnd();

    glColor3f(0.3,0.7,0.3); // lighter green
    drawFilledCircle(4,45,15);

    glPopMatrix();
}

// -------- BUILDING --------
void drawBuilding(float x,float y)
{
    glColor3f(0.6,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(x,y);
    glVertex2f(x+60,y);
    glVertex2f(x+60,y+150);
    glVertex2f(x,y+150);
    glEnd();

    glColor3f(0.8,0.9,1);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            glBegin(GL_POLYGON);
            glVertex2f(x+10+i*15,y+20+j*30);
            glVertex2f(x+20+i*15,y+20+j*30);
            glVertex2f(x+20+i*15,y+35+j*30);
            glVertex2f(x+10+i*15,y+35+j*30);
            glEnd();
        }
    }
}


// --------Far BUILDING --------
void drawFarBuilding(float x,float y)
{
    glPushMatrix();

    glTranslatef(x,y,0);
    glScalef(0.5,0.5,1);   // smaller = far

    glColor3f(0.7,0.7,0.8); // faded color

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(60,0);
    glVertex2f(60,120);
    glVertex2f(0,120);
    glEnd();

    glPopMatrix();
}


// -------- HUMAN (BETTER GRAPHICS) --------
void drawHuman(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    // head
    glColor3f(1.0, 0.8, 0.6);
    drawFilledCircle(0, 30, 6);

    // body (shirt)
    glColor3f(0.2, 0.4, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(-5, 25);
    glVertex2f(5, 25);
    glVertex2f(8, 10);
    glVertex2f(-8, 10);
    glEnd();

    // legs
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-6, 10);
    glVertex2f(-2, 10);
    glVertex2f(-2, 0);
    glVertex2f(-6, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(2, 10);
    glVertex2f(6, 10);
    glVertex2f(6, 0);
    glVertex2f(2, 0);
    glEnd();

    // arms
    glColor3f(1.0, 0.8, 0.6);
    glBegin(GL_LINES);
    glVertex2f(-8, 20);
    glVertex2f(-15, 15);

    glVertex2f(8, 20);
    glVertex2f(15, 15);
    glEnd();



    glPopMatrix();
}


   // -------- CLOUD --------
void drawCloud(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glColor3f(1.0, 1.0, 1.0);

    // main cloud (multiple circles)
    drawFilledCircle(0,0,20);
    drawFilledCircle(20,5,18);
    drawFilledCircle(-20,5,18);
    drawFilledCircle(10,15,15);
    drawFilledCircle(-10,15,15);

    glPopMatrix();
}

// -------- DISPLAY --------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // -------- PROJECTION --------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(is3D)
    {
        glEnable(GL_DEPTH_TEST);
        gluPerspective(60, 1, 1, 2000);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
        gluOrtho2D(-500,500,-300,300);
    }

    // -------- MODEL VIEW --------
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(is3D)
    {
        gluLookAt(0,150,500,
                  0,0,0,
                  0,1,0);

        glRotatef(angleX,1,0,0);
        glRotatef(angleY,0,1,0);
    }



    // -------- SKY --------
glColor3f(0.7,0.9,1);
glBegin(GL_POLYGON);
glVertex2f(-500,100);
glVertex2f(500,100);
glVertex2f(500,300);
glVertex2f(-500,300);
glEnd();

// -------- CLOUDS --------
drawCloud(cloudX1, 220);
drawCloud(cloudX2, 250);

    // -------- FAR BACKGROUND (VISIBLE ABOVE ROAD) --------
    drawFarBuilding(-400,140);
    drawFarBuilding(-250,150);
    drawFarBuilding(-100,135);
    drawFarBuilding(50,145);
    drawFarBuilding(200,140);

    drawFarTree(-350,140);
    drawFarTree(-200,150);
    drawFarTree(100,140);
    drawFarTree(250,150);

    // -------- MID OBJECTS (GROUND LEVEL) --------
    drawTree(-400,70);
    drawTree(-300,70);
    drawTree(250,70);
    drawTree(350,70);

    drawBuilding(-450,80);
    drawBuilding(300,80);

    // -------- FRONT --------
    drawRoad();     // covers lower part only
    drawSignal();

    drawCar(carX,0,0.9,0.1,0.1);
    drawCar(car2X,0,0.1,0.3,0.9);
    drawCar(car3X,0,0.1,0.8,0.2);

    drawBike(carX - 150,-20);
    drawBike(car2X - 200,20);

    drawHuman(-200, human1Y);
    drawHuman(-120, human2Y);
    drawHuman(180, 70);
    drawHuman(260, 70);

    glutSwapBuffers();
}





// -------- UPDATE --------
void update()
{
    wheelRot += 0.3;



    // -------- DISTANCE CONTROL (ONLY WHEN VISIBLE) --------
if(carX > -500 && car2X > -500)
{
    if(car2X > carX - 120)
        car2X = carX - 120;   // lock position instead of moving backward
}

if(car2X > -500 && car3X > -500)
{
    if(car3X > car2X - 120)
        car3X = car2X - 120;
}

// -------- FORWARD MOVEMENT --------
if(!(signal==0 && carX>-50 && carX<50))
    carX += 0.05;

if(!(signal==0 && car2X>-50 && car2X<50))
    car2X += 0.045;

if(!(signal==0 && car3X>-50 && car3X<50))
    car3X += 0.04;

// -------- RESET (ALLOW FULL EXIT) --------
if(carX > 650) carX = -600;
if(car2X > 650) car2X = -750;
if(car3X > 650) car3X = -900;

    // -------- DELAY BEFORE CROSS --------
if(startCross && !cross)
{
    crossDelay += 0.0001;   // controls delay speed

    if(crossDelay > 1)  // ~0.5 second delay
    {
        cross = 1;
        startCross = 0;
    }
}

  // -------- HUMAN CROSSING --------
if(cross && !crossed)
{
    if(human1Y > -80) human1Y -= 0.05;
    if(human2Y > -80) human2Y -= 0.05;

    if(human1Y <= -80 && human2Y <= -80)
        crossed = 1;
}

// -------- CLOUD MOVEMENT --------
cloudX1 += 0.02;
cloudX2 += 0.015;

if(cloudX1 > 600) cloudX1 = -600;
if(cloudX2 > 600) cloudX2 = -600;


glutPostRedisplay();
}
// -------- KEYBOARD --------
void keyboard(unsigned char key,int x,int y)
{
    if(key=='r'){
        signal = 0;
        crossDelay = 0;
        startCross = 1;
    }

    if(key=='g'){
        signal = 1;
        cross = 0;
        startCross = 0;
    }

    // -------- MODE SWITCH --------
    if(key=='2') is3D = 0;
    if(key=='3') is3D = 1;
}

void specialKeys(int key, int x, int y)
{
    if(is3D)
    {
        if(key==GLUT_KEY_UP) angleX += 5;
        if(key==GLUT_KEY_DOWN) angleX -= 5;
        if(key==GLUT_KEY_LEFT) angleY -= 5;
        if(key==GLUT_KEY_RIGHT) angleY += 5;
    }
}



// -------- INIT --------
void init()
{
    glEnable(GL_DEPTH_TEST);   // REQUIRED for 3D
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.5,0.8,1,1);
}

// -------- MAIN --------
int main(int argc,char** argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800,600);
    glutCreateWindow("Smart Traffic Simulation");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
}


