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
#elif _WIN64
#include <GLUT/freeglut.h>
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

    if (life == 0)
        return;
    
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

float Block::
getX() {
    return xpos;
}