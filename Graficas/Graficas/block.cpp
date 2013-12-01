//
//  block.cpp
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <GL/freeglut.h>
#endif

#include <math.h>
#include <stdio.h>
#include "block.h"


Block::Block(){
}

Block::~Block(){
    
}

void Block::initBlock(float x, float y, int t, int b){
    xpos = x;
    ypos = y;
    type = t;

    if (type == 0)      //Normal
        life = 1;
    else                //Special
        life = 2;
    
    if (b == 0)         //Normal
        bonus = 0;
    else if (b == 1)    //Size
        bonus = 1;
    else if (b == 2)    //Speed
        bonus = 2;
        
}

void Block::drawUndamaged() {
    
    glBegin(GL_LINES);
    //bottomline
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    //leftline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    //rightline
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    //topline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glEnd();

}

void Block::drawDamaged() {
    
    glBegin(GL_LINES);
    //////////////LEFT
    //bottomlineLeft
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    glVertex3f(xpos-0.2, ypos-0.25, 0.0);

    //bottomCenterCrackLeft
    glVertex3f(xpos-0.35, ypos-0.05, 0.0);
    glVertex3f(xpos-0.2, ypos-0.25, 0.0);

    //centerCenterCrackLeft
    glVertex3f(xpos-0.35, ypos-0.05, 0.0);
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);

    //topCenterCrackLeft
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);
    glVertex3f(xpos+0.0, ypos+0.25, 0.0);
    
    //leftCenterCrackBottom
    glVertex3f(xpos-1.0, ypos-0.1, 0.0);
    glVertex3f(xpos-0.3, ypos-0.05, 0.0);
    
    //leftCenterCrackTop
    glVertex3f(xpos-1.0, ypos+0.1, 0.0);
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);

    //leftline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    
    //toplineLeft
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+0.0, ypos+0.25, 0.0);
    
    //////////////RIGHT
    //bottomlineRight
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+0.0, ypos-0.25, 0.0);

    //bottomCenterCrakRight
    glVertex3f(xpos+0.0, ypos-0.25, 0.0);
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    
    //centerCenterCrakRight
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);
    
    //centerTopCrackRight
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);
    glVertex3f(xpos+0.25, ypos+0.25, 0.0);
    
    //rightCenterCrackBottom
    glVertex3f(xpos+1.0, ypos-0.04, 0.0);
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    
    //rightCenterCrackTop
    glVertex3f(xpos+1.0, ypos+0.1, 0.0);
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);

    //bottomlineRight
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+0.1, ypos-0.25, 0.0);
    
    //rightline
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    
    //toplineRight
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+0.25, ypos+0.25, 0.0);

    glEnd();
    
}

void Block::drawBlock(){

    if (life < 0)
        return;
    
    if (life == 0) {
		//if (type == 1)
//		glutTimerFunc(500,boom,0);
        life--;
        return;
    }
    
    glPointSize(10.0);
    if (bonus == 1) {
        glColor4f(0.5, 0.5, 0.5, 1.0);
        glBegin(GL_POINTS);
        glVertex3f(xpos, ypos, 0.0);
        glEnd();
    } else if (bonus == 2) {
        glColor4f(0.3, 0.5, 0.8, 1.0);
        glBegin(GL_POINTS);
        glVertex3f(xpos, ypos, 0.0);
        glEnd();
    }
    if (type == 0) {
        glColor4f(1.0, 1.0, 1.0, 1.0);
        drawUndamaged();
    } else {
        glColor4f(1.0, 0.0, 0.0, 1.0);
        if (life == 2)
            drawUndamaged();
        else
            drawDamaged();
    }
}

float Block::getX() {
    return xpos;
}

void Block::boom(int value) {

	float vExp[5][10];
	float ep0, ep1, p0, p1, t, ratio;
	ratio = 1.0;

//    vExp[0][0] = sin(gradToRad(15.0));
//    vExp[1][0] = cos(gradToRad(15.0));
//    
//    vExp[0][1] = sin(gradToRad(255.0));
//    vExp[1][1] = cos(gradToRad(255.0));
//    
//    vExp[0][2] = sin(gradToRad(127.0));
//    vExp[1][2] = cos(gradToRad(127.0));
//    
//    vExp[0][3] = sin(gradToRad(90.0));
//    vExp[1][3] = cos(gradToRad(90.0));
//    
//    vExp[0][4] = sin(gradToRad(180.0));
//    vExp[1][4] = cos(gradToRad(180.0));
//    
//    vExp[0][5] = sin(gradToRad(270.0));
//    vExp[1][5] = cos(gradToRad(270.0));
//    
//    vExp[0][6] = sin(gradToRad(45.0));
//    vExp[1][6] = cos(gradToRad(-45.0));
//    
//    vExp[0][7] = sin(gradToRad(325.0));
//    vExp[1][7] = cos(gradToRad(325.0));
//    
//    vExp[0][8] = sin(gradToRad(73.0));
//    vExp[1][8] = cos(gradToRad(73.0));
//    
//    vExp[0][9] = sin(gradToRad(225.0));
//    vExp[1][9] = cos(gradToRad(225.0));

	t = 0.0;
	float cxR, cyR;
	cxR = xpos;
	cyR= ypos;

	printf("cxR: %f, cyR: %f y t: %f iniciales\n\n", cxR, cyR, t);

	for(int i=0; i<10; i++){

		printf("Entre en el for\n");

		glPointSize(5.0);
		glBegin(GL_POINTS); 
			//for (int j= 0; j<10; j++) {  
				glVertex3f( cxR + vExp[1][i] * ratio, cyR + vExp[0][i] * ratio, 0.0 ); 
			//}
		glEnd();

		t += 0.2;

		cxR = xpos + t*vExp[1][i] + (1-t)* vExp[1][i+1];
		cyR = ypos + t*vExp[0][i] + (1-t)* vExp[0][i+1];

		printf("cxR: %f, cyR: %f y t: %f iteracion %d\n\n", cxR, cyR, t, i);

	}

//	glutTimerFunc(500,boom,0);
	glutPostRedisplay();
}

int Block::getLife() {
    return life;
}

void Block::changeLife(int l) {
    life--;
}

float Block::gradToRad(float g) {
	float rad;
	rad = g*M_PI/180;
	return rad;
}
