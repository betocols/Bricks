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
int i = 0, isAboom = 0, x, o = 0, stop = 0;
int win = 0;
float t=0.0, xboom = 0.0, yboom = 0.0;
float vExp[4][10]; ///Array to obtain the positions of the boom

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

void gotBonus() {
    int pos;
    for (int j = 0; j < 5; j++){
        pos = bonus[j];
        //Checks if the bonus is at the height of the platform
        if ((blocks[pos].getY() >= -8.8) && (blocks[pos].getY() <= -8.5)) {

            //Checks if the bonus is at reach of the platform
            if ((blocks[pos].getX() <= p.getX() + p.getSize() + 0.3)
                  && (blocks[pos].getX() >= p.getX() - p.getSize() - 0.3)) {

                if (blocks[pos].getBonus() == 2) {
                    blocks[pos].setBonus(0);
                    p.increaseSize();
                } else if (blocks[pos].getBonus() == 1) {
                    b.increaseSpeed();
                    blocks[pos].setBonus(0);
                }
                
            }
        }
    }
}

void drawBoom(float v[4][10]) {

	for (int j= 0; j<10; j++) {
		glBegin(GL_POINTS);
			glPointSize(2.0);
			glColor3f(1.0,0.0,1.0);
			glVertex3f(v[3][j], v[2][j], 0.0);
			glPointSize(1.0);
			glColor3f(0.0,0.0,0.0);
			glVertex3f(v[3][j], v[2][j], 0.0);
		glEnd();
	}

}

void initBoom() {

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
    vExp[1][6] = cos(gradToRad(45.0));
    
    vExp[0][7] = sin(gradToRad(325.0));
    vExp[1][7] = cos(gradToRad(325.0));
    
    vExp[0][8] = sin(gradToRad(73.0));
    vExp[1][8] = cos(gradToRad(73.0));
    
    vExp[0][9] = sin(gradToRad(225.0));
    vExp[1][9] = cos(gradToRad(225.0));

}

void boom(int value) {
 
	
	float radio = 1.0;
	float cxR, cyR;

	for(int i=0; i<10; i++){
        
		cyR = yboom + (t)*vExp[0][i]*radio;
		cxR = xboom + (t)*vExp[1][i]*radio;

		printf("sen %f cos %f \n", vExp[0][i], vExp[1][i]);

		vExp[2][i] = cyR;
		vExp[3][i] = cxR;

	}
        
	glutPostRedisplay();
	t += 0.1;

	if (t >= 1.0) {
		t = -0.1;
		return;

	}
	glutTimerFunc(100, boom, 0);
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
        x = blocks[i].drawBlock();
        if (x==-2 || x==0) {
            win++;
            if (win == 35)
                b.setStop(0);
		}
		if (x == -2) {
            isAboom = i;
			xboom = blocks[isAboom].getX();
			yboom = blocks[isAboom].getY();
			t += 0.1;
            boom(0);
		}
    }
    
    if (b.getSpeed() == 0.0 && b.getStop() == 1)
        b.drawDirection();
    

	if ((t > -0.1) && (t <= 1.0) && (t != 0.0))
		drawBoom(vExp);

    b.drawBall(0.0, 0.0, 0.0);
    
    //If all the blocks were destroyed
    if (win == 35) {
        glBegin(GL_POINTS);
        glVertex3d(0.0, 0.0, 0.0);
        glEnd();
    }
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    if (b.getStop() == 0)
        switch (key) {
            case 's':                   //Restarts game
//                //Gets the special blocks
//                initRands();
//                b.initBall();
//                p.initPlatform();
                win = 0;
                b.setStop(1);
                //Blocks Initializing
                i = 0;
                for (float x = -8.4; x <= 8.5; x += 2.8) {
                    for (float y = 7.5; y > 1.0; y -= 1.5) {
                        blocks[i].initBlock(i, x, y, isSpe(i), isBon(i));
                        i++;
                    }
                }
                break;
            case 'a':
            case 'A':
                b.changeR(-10.0);
                break;
                //        case GLUT_KEY_RIGHT:
            case 'd':
            case 'D':
                b.changeR(10.0);
                break;
                
            case 27:                    //Ends game
                exit(0);
                break;
                
            default:
                break;
        }
    else
        switch(key)
        {
    //        case GLUT_KEY_LEFT:
                
            case 'j':
            case 'J':
                if (b.getSpeed() == 0.0)
                    b.changeR(10.0);
                else
                    p.moveX(-0.5);
                break;
    //        case GLUT_KEY_RIGHT:
            case 'l':
            case 'L':
                if (b.getSpeed() == 0.0)
                    b.changeR(-10.0);
                else
                    p.moveX(0.5);
                break;
                //        case GLUT_KEY_RIGHT:
            case 'a':
            case 'A':
                b.changeR(10.0);
                break;
                //        case GLUT_KEY_RIGHT:
            case 'd':
            case 'D':
                b.changeR(-10.0);
                break;
            case 'b':
                blocks[o++ % 35].changeLife(-1);
                break;
//            case '1':
//                p.resetSize();
//                break;
//            case '2':
//                p.increaseSize();
//                break;
            case 32:
                b.resetSpeed();
                break;
//            case '4':
//                b.increaseSpeed();
//                break;
            case 27:   // escape
                exit(0);
                break;
                
            default:
                break;
        }
    
    render();
}

void TimeEvent(int value) {
    
    b.boing(p, blocks);
    gotBonus();
	glutPostRedisplay();
	glutTimerFunc(17, TimeEvent, 1);

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
            blocks[i].initBlock(i, x, y, isSpe(i), isBon(i));
            i++;
        }
    }

	initBoom();
    
    glutTimerFunc(17, TimeEvent, 1);
    glutMainLoop();
    return 0;
    
}