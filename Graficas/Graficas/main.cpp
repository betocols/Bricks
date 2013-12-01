//
//  main.cpp
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//
#include <GL/glew.h>
#include <ctime>
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <GL/freeglut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "ball.h"

using namespace std;

#define DEF_floorGridScale  1.0
#define DEF_floorGridXSteps 10.0
#define DEF_floorGridZSteps 10.0
Block blocks[35];                   //Array of blocks
int special[7];                     //Array to obtain the number of the especial blocks
int bonus[5];                       //Array to obtain the number of the bonus blocks
Platform p;
Ball b;
int i = 0;

void changeViewport(int w, int h) {
    
    float aspectratio;
    
    if (h==0)
        h=1;
    
    
    glViewport(0,0,w,h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    
    aspectratio = (float) w / (float) h;
    
    if (w<=h) {
        
        glOrtho(-10.0,10.0,-10.0/aspectratio,10.0/aspectratio,1.0,50.0);
        
    }else {
        
        glOrtho(-10.0*aspectratio,10.0*aspectratio,-10.0,10.0,1.0,50.0);
        
    }
    
    
    glMatrixMode (GL_MODELVIEW);
}

//Draws the border of the game
void gameset() {
    //GameBorder
    glBegin(GL_LINES);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    //Left Column
    glVertex3f(-10.0, -9.0, 0.0);
    glVertex3f(-10.5, -9.0, 0.0);
    
    glVertex3f(-10.0, -9.0, 0.0);
    glVertex3f(-10.0, 9.0, 0.0);
    
    glVertex3f(-10.5, -9.0, 0.0);
    glVertex3f(-10.5, 9.5, 0.0);
    
    glVertex3f(-10.0, 9.0, 0.0);
    glVertex3f(-10.5, 9.5, 0.0);
    
    //Top Column
    glVertex3f(-10.5, 9.5, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(-10.0, 9.0, 0.0);
    glVertex3f(10.0, 9.0, 0.0);
    
    //Right Column
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.0, 9.0, 0.0);
    
    glVertex3f(10.0, 9.0, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(10.5, -9.0, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.5, -9.0, 0.0);
    
    glEnd();
    //End GameBorder
    

}

//Fills the special array with the number of the blocks that are special and that have bonus
void initRands(){
    int randNum;
    int j = 1, k;

    
    //Sets seed to get random number every time
    srand ( (unsigned)time(NULL));
    //Assign the first random value
    special[0] = rand()% 34;

    while (j < 7){
        randNum = rand()% 34;
        
        for (k = 0; k < j; k++) {
            if (special[k] == randNum)
                break;
        }

        if (k == j){
            special[j] = randNum;
            j++;
        }
        
        
    }
    
    j = 0;
    bonus[0] = rand()% 34;
    while (j < 5){
        randNum = rand()% 34;
        
        for (k = 0; k < j; k++) {
            if (bonus[k] == randNum)
                break;
        }
        
        if (k == j){
            bonus[j] = randNum;
            j++;
        }
        
        
    }
}

//Determines wether the number is special or not
int isSpe(int e){
    for(int j = 0; j < 7; j++)
        if (special[j] == e)
            return 1;
    
    return 0;
}

//Determines wether the number is special or not
int isBon(int e){
    int j;
    
    for(j = 0; j < 5; j++)
        if (bonus[j] == e)
            break;
    
    if (j == 5)
        return 0;
    
    return rand()% 2 + 1;
}

float gradToRad(float g) {
	float rad;
	rad = g*M_PI/180;
	return rad;
}

void drawBoom(float cxR, float cyR, float vExp[5][10], float ratio) {
    
    glPointSize(5.0);
    glBegin(GL_POINTS);
    //for (int j= 0; j<10; j++) {
        glVertex3f( cxR + vExp[1][i] * ratio, cyR + vExp[0][i] * ratio, 0.0 );
    //}
    glEnd();
    
}

void boom(int value) {
    
	float vExp[5][10];
	float t, ratio;
	float cxR, cyR;
    t = 0.0;
	ratio = 1.0;
    
    vExp[0][0] = sin(gradToRad(15.0));
    vExp[1][0] = cos(gradToRad(15.0));
    
    vExp[0][1] = sin(gradToRad(255.0));
    vExp[1][1] = cos(gradToRad(255.0));
    
    vExp[0][2] = sin(gradToRad(127.0));
    vExp[1][2] = cos(gradToRad(127.0));
    
    vExp[0][3] = sin(gradToRad(90.0));
    vExp[1][3] = cos(gradToRad(90.0));
    
    vExp[0][4] = sin(gradToRad(180.0));
    vExp[1][4] = cos(gradToRad(180.0));
    
    vExp[0][5] = sin(gradToRad(270.0));
    vExp[1][5] = cos(gradToRad(270.0));
    
    vExp[0][6] = sin(gradToRad(45.0));
    vExp[1][6] = cos(gradToRad(-45.0));
    
    vExp[0][7] = sin(gradToRad(325.0));
    vExp[1][7] = cos(gradToRad(325.0));
    
    vExp[0][8] = sin(gradToRad(73.0));
    vExp[1][8] = cos(gradToRad(73.0));
    
    vExp[0][9] = sin(gradToRad(225.0));
    vExp[1][9] = cos(gradToRad(225.0));
    
	cxR = blocks[i].getX();
	cyR= blocks[i].getY();
    
	printf("cxR: %f, cyR: %f y t: %f iniciales\n\n", cxR, cyR, t);
    
	for(int i=0; i<10; i++){
        
		printf("Entre en el for\n");
        
        drawBoom(cxR, cyR, vExp, ratio);
        
		t += 0.2;
        
		cxR = blocks[i].getX() + t*vExp[1][i] + (1-t)* vExp[1][i+1];
		cyR = blocks[i].getY() + t*vExp[0][i] + (1-t)* vExp[0][i+1];
        
		printf("cxR: %f, cyR: %f y t: %f iteracion %d\n\n", cxR, cyR, t, i);
        
	}
    
    glutTimerFunc(500,boom,1);
	glutPostRedisplay();
}

void render(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
    //Suaviza las lineas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POINT_SMOOTH );    
    
    gameset();
    
    p.drawPlatform();
    
    for(i = 0; i < 35; i++) {
        if (blocks[i].drawBlock()==-2 || blocks[i].drawBlock()==0)
            glutTimerFunc(500,boom,0);
    }
    
    b.drawBall(0.0, 0.0, 0.0);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    switch(key)
    {
//        case GLUT_KEY_LEFT:
        case 'j':
        case 'J':
            p.moveX(-0.5);
            break;
//        case GLUT_KEY_RIGHT:
        case 'l':
        case 'L':
            p.moveX(0.5);
            break;
            //        case GLUT_KEY_RIGHT:
        case 'a':
        case 'A':
            b.changeR(-45.0);
            break;
            //        case GLUT_KEY_RIGHT:
        case 'd':
        case 'D':
            b.changeR(45.0);
            break;
        case 'b':
            blocks[0].changeLife(-1);
            break;
        case '1':
            p.resetSize();
            break;
        case '2':
            p.increaseSize();
            break;
        case '3':
                b.resetSpeed();
            break;
        case '4':
                b.increaseSpeed();
            break;
        case 27:   // escape
            exit(0);
            break;
            
        default:
            break;
    }
    
    render();
}

void TimeEvent(int te)
{
    
    b.drawBall(0.0, 0.1, 0.0);
    b.boing(p);
	glutPostRedisplay();
	glutTimerFunc(100, TimeEvent, 1);

}

int main (int argc, char** argv) {
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(900,700);
    
    glutCreateWindow("Proyecto 2");
    
    glutReshapeFunc(changeViewport);
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    }
    
    //Gets the special blocks
    initRands();
    //Blocks Initializing
    for (float x = -8.4; x <= 8.5; x += 2.8) {
        for (float y = 7.5; y > 1.0; y -= 1.5) {
            blocks[i].initBlock(x, y, isSpe(i), isBon(i));
            i++;
        }
    }
    
    glutTimerFunc( 10, TimeEvent, 1);
    glutMainLoop();
    return 0;
    
}