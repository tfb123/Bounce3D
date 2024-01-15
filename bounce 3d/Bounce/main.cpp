#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define PI 3.141592
//aplinkos stilius
#define DRAFT 0
#define BEST 1

int cameraSpin = TRUE;
int ballBounce = TRUE;
int cameraDirection = 1;
float cameraSpeed = 0.1;
float ballSpeed = 0.05;
float upDownRotate = 45;
int quality = DRAFT;

void CreateObjects()
{
    float shine[]={5};//sphere shininess
    float diffSph[]={0.5,0,0.5,1};

    //green polygon
    float ambient1[]={0,1,0,1};
    float diff1[]={0,0.2,0,1};
    //cubes
    float ambient2[]={0,8,0.8,0,1};
    float diff2[]={0.2,0.2,0,1};



    if (quality==DRAFT)
    {
        glBegin(GL_LINE_LOOP);
    }
    else
    {
        glBegin(GL_POLYGON);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient1);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diff1);
    }

    glColor3f(0,1,0);
    glNormal3f(0,1,0);
    glVertex3f(15,0,15);
    glVertex3f(15,0,-15);
    glVertex3f(-15,0,-15);
    glVertex3f(-15,0,15);

    glEnd();

    //kubas
    glPushMatrix();
    glColor3f(0.8,0.8,0.8);
    glTranslatef(13.5,1.5,13.5);
    if (quality==DRAFT)
    {
        glutWireCube(3);
    }
    else
    {
        glutSolidCube(3);
    }

    //antras kubas
    glTranslatef(-27,0,0);
    if (quality==DRAFT)
    {
        glutWireCube(3);
    }
    else
    {
        glutSolidCube(3);
    }
    glPopMatrix();
    //sphere
    glPushMatrix();
     //translate
    static float th = 0;
    glTranslatef(0,2+6*(1+sin(th*PI/180)),0);
    if (ballBounce==TRUE)
        th+=ballSpeed;
    glColor3f(0.5,0,0.5);
    if (quality==DRAFT)
    {
        glutWireSphere(3,20,20);
    }
    else
    {
        glMaterialfv(GL_FRONT,GL_SHININESS,shine);
        glutSolidSphere(3,20,20);
    }

    glPopMatrix();
    //lankassssssssss
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
    for (int i=0;i<180;i++)
    {
        glVertex3f(15*cos(i*PI/180),7*sin(i*PI/180),-15);
    }
    glEnd();
}

void CreateCamera()
{
    static float th=0;
    gluPerspective(10,1,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
              25*cos(th*PI/180)*sin(upDownRotate*PI/180),
              25*cos(upDownRotate*PI/180),
              25*sin(th*PI/180)*sin(upDownRotate*PI/180),
              0,0,0,
              0,1,0
              );
    if (cameraSpin==TRUE)
        th+=cameraDirection*cameraSpeed;
}

void CreateLight()
{
    float ambient[]={0.5,0.5,0,1};

    //light source
    //upper
    float pos1[]={-10,10,0,0};//last 0 - infinite distance
    //bottom
    float pos2[]={10,-10,0,0};

    float dif1[]={0.8,0.8,0.8,1};
    float dif2[]={0.4,0.4,0.4,1};

    if (quality==BEST)
    {

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);

    glLightfv(GL_LIGHT0,GL_POSITION,pos1);
    glLightfv(GL_LIGHT1,GL_POSITION,pos2);

    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif1);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,dif2);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    }
}

void ManoVaizdas()//pagrindine paisymo funkcija
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//buferio valymo funkcija

    glPushMatrix();
        CreateLight();
        CreateCamera();
        CreateObjects();


    glPopMatrix();

    //glFlush();//refresh
    glutSwapBuffers();
    glutPostRedisplay();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    if (quality==DRAFT)
        glShadeModel(GL_FLAT);
    else
    {
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glShadeModel(GL_SMOOTH);
    }

    glLineWidth(1);
    glPointSize(1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0,0,0,0);//background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(-400,400,-300,300);
    glOrtho(-20,20,-20,20,-20,20);

}

void HandleMainMenu(int menu)
{
    if (menu==1)
    {
        cameraSpin = !cameraSpin;

    }
    else if (menu==2)
    {
        ballBounce = !ballBounce;
    }
    else if (menu==3)
    {
        cameraDirection *=-1;
    }
}

void HandleBallMenu(int menu)
{
    if (menu==1)
    {
        ballSpeed = 0.02;

    }
    else if (menu==2)
    {
        ballSpeed =  0.1;
    }
    else if (menu==3)
    {
        ballSpeed =  1.5;
    }
    else if (menu==4)
    {
        ballSpeed =  2;
    }
}

void HandleCameraMenu(int menu)
{
    if (menu==1)
    {
        cameraSpeed = 0.1;

    }
    else if (menu==2)
    {
        cameraSpeed =  0.25;
    }
    else if (menu==3)
    {
        cameraSpeed =  0.5;
    }
    else if (menu==4)
    {
        cameraSpeed =  1;
    }
}

void HandleQualityMenu(int menu)
{
    if (menu==1)
    {
        quality = BEST;

    }
    else if (menu==2)
    {
        quality = DRAFT;
    }

}

void SpecKlavisai(int key, int x, int y)
{
    if (key==GLUT_KEY_RIGHT)
    {
        cameraDirection = 1;
    }
    else if (key==GLUT_KEY_LEFT)
    {
        cameraDirection = -1;
    }
    else if (key==GLUT_KEY_UP)
    {
        upDownRotate-=2;
    }
    else if (key==GLUT_KEY_DOWN)
    {
        upDownRotate+=2;
    }
}

void Klavisai(unsigned char key, int x, int y)
{
    if (tolower(key)=='b')
    {
        ballBounce = !ballBounce;
    }
    else if (tolower(key)=='c')
    {
        cameraDirection *=-1;
    }
    else if (key==27)
    {
       exit(0);
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc,argv);//grafikos inicializavimas
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Mano Pirma proga");
    glutDisplayFunc(ManoVaizdas);
    glutSpecialFunc(SpecKlavisai);
    glutKeyboardFunc(Klavisai);
    init();

    int mainMenu;
    int ballMenu;
    int cameraMenu;
    int qualityMenu;

    qualityMenu = glutCreateMenu(HandleQualityMenu);
    glutAddMenuEntry("Best",1);
    glutAddMenuEntry("Draft",2);

    cameraMenu = glutCreateMenu(HandleCameraMenu);
    glutAddMenuEntry("Slow",1);
    glutAddMenuEntry("Normal",2);
    glutAddMenuEntry("Fast",3);
    glutAddMenuEntry("Ultra Fast",4);

    ballMenu = glutCreateMenu(HandleBallMenu);
    glutAddMenuEntry("Slow",1);
    glutAddMenuEntry("Normal",2);
    glutAddMenuEntry("Fast",3);
    glutAddMenuEntry("Ultra Fast",4);

    mainMenu = glutCreateMenu(HandleMainMenu);
    glutAddMenuEntry("Toggle Camera Spin",1);
    glutAddMenuEntry("Toggle Camera Direction",3);
    glutAddSubMenu("Camera Speed",cameraMenu);
    glutAddMenuEntry("Toggle Ball Bounce",2);
    glutAddSubMenu("Ball Speed",ballMenu);
    glutAddSubMenu("Toggle Quality Menu",qualityMenu);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
