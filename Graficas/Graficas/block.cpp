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

    if (life == 0) {
        boom();
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

void Block::boom() {

	float vExp[5][10];
	float ep0, ep1, p0, p1, t, ratio;
	ratio = 1.0;

	vExp[0][0] = sin(0.15);
	vExp[1][0] = cos(0.15);

	vExp[0][1] = sin(0.25);
	vExp[1][1] = cos(0.25);

	vExp[0][2] = sin(0.49);
	vExp[1][2] = cos(0.49);

	vExp[0][3] = sin(0.90);
	vExp[1][3] = cos(0.90);

	vExp[0][4] = sin(0.01);
	vExp[1][4] = cos(0.01);

	vExp[0][5] = sin(0.32);
	vExp[1][5] = cos(0.32);

	vExp[0][6] = sin(0.45);
	vExp[1][6] = cos(0.45);

	vExp[0][7] = sin(0.88);
	vExp[1][7] = cos(0.88);

	vExp[0][8] = sin(0.73);
	vExp[1][8] = cos(0.73);

	vExp[0][9] = sin(0.64);
	vExp[1][9] = cos(0.64);

	glBegin(GL_LINE_LOOP); 
		for (int i= 0; i<10; i++) {  
			glVertex3f( xpos + vExp[1][i] * ratio, ypos + vExp[0][i] * ratio, 0.0 ); 
		} 
	glEnd();

	//velocidad

	//ep0 = (1-t)*p0 + t*p1;
	//ep1 = (1-t)*p0 + t*p1;

	//t+=0.2;
}

void Block::changeLife(int l) {
    life -= l;
}

