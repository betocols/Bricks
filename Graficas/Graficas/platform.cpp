//
//  platform.cpp
//  Graficas
//
//  Created by Alberto Cols on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <GL/freeglut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "platform.h"


Platform::Platform() {
    xpos = 0.0;
    size = 1.0;
    life = 3;
}

Platform::~Platform() {
    
}

int Platform::getSize() {
    return size;
}

int Platform::forWho(int who) {
    
    if  (who == 0)
        increaseSize();
    if (who == 1)
        return 1;
    
    return 0;
}

void Platform::increaseSize() {
    float left, right;
    
    size *= 1.05;
    
    //size top is 1.05^5
    if (size > 1.27681) {
        size = 1.27681;
        printf("Platform at top: %f\n", size);
    } else
        printf("Platform increased: %f\n", size);
    
    //If the platform increases it size next to a border,
    //moves the center so it doesnt pass the border
    left = xpos - size;
    right = xpos + size;
    if (left <= -10.0)
        xpos = -10.0 + size;
    else if (right >= 10.0)
        xpos = 10.0 - size;
    
}

void Platform::resetSize() {
    size = 1.0;
    printf("Platform reset: %f\n", size);
}

float Platform::getX() {
    return xpos;
}

void Platform::moveX(float x) {
    float t = xpos + x;
    float left = t - size;
    float right = t + size;
    
    //If the platform is inside the boundaries of the field
    if ((t >= -10.0 + size) && (t <= 10.0 - size)) {
        xpos += x;
    }
    
    //If it tries to go outside the boundaries, it takes the platform back
    if (left < -10.0) {
        xpos = -10.0 + size;
        
    } else if (right > 10.0) {
        xpos = 10.0 - size;
        
    }
}

int Platform::getLife() {
    return life;
}

void Platform::changeLife(int l) {
    if ((l == 1) || life == -1) {
        life += l;
    } else {
        life = l;
    }
}

void Platform::drawPlatform() {
    //Platform
    glBegin(GL_LINES);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3f(xpos-size, -9.0, 0.0);
    glVertex3f(xpos+size, -9.0, 0.0);
    
    glVertex3f(xpos-size, -9.0, 0.0);
    glVertex3f(xpos-size, -8.5, 0.0);
    
    glVertex3f(xpos+size, -9.0, 0.0);
    glVertex3f(xpos+size, -8.5, 0.0);
    
    glVertex3f(xpos-size, -8.5, 0.0);
    glVertex3f(xpos+size, -8.5, 0.0);
    
    glEnd();
    //End Platform
    
}



