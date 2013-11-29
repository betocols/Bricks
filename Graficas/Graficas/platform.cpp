//
//  platform.cpp
//  Graficas
//
//  Created by Alberto Cols on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdio.h>
#include "platform.h"

Platform::Platform() {
    xpos = 0;
    bonus = 0;
    life = 3;
}

Platform::~Platform() {
    
}

void Platform::drawPlatform() {
    //Platform
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3f(xpos-1.0, -9.0, 0.0);
    glVertex3f(xpos+1.0, -9.0, 0.0);
    
    glVertex3f(xpos-1.0, -9.0, 0.0);
    glVertex3f(xpos-1.0, -8.5, 0.0);
    
    glVertex3f(xpos+1.0, -9.0, 0.0);
    glVertex3f(xpos+1.0, -8.5, 0.0);
    
    glVertex3f(xpos-1.0, -8.5, 0.0);
    glVertex3f(xpos+1.0, -8.5, 0.0);
    
    glEnd();
    //End Platform

}

int Platform::getX() {
    return xpos;
}

void Platform::moveX(float x) {
    float t = xpos + x;
    if ((t >= -11.0) && (t <= 11.0)) {
        xpos += x;
    }
}

int Platform::getBonus() {
    return bonus;
}

void Platform::setBonus(int b) {
    bonus = b;
}