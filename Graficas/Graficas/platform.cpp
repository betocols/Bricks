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

void Platform::changeSize(float b) {
    float left, right;
    //Takes the size of the platform back to normal
    if (b == 1.0)
        size = 1.0;
    //Increases the size of the platform
    else {
        size *= 1.05;
        
        //size top is 1.05^5
        if (size > 1.27681)
            size = 1.27681;
        
        //If the platform increases it size next to a border,
        //moves the center so it doesnt pass the border
        left = xpos - size;
        right = xpos + size;
        if (left <= -10.0)
            xpos = -10.0 + size;
        else if (right >= 10.0)
            xpos = 10.0 - size;
    }
    
    printf("size %f, b %f\n", size, b);
}

int Platform::getX() {
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



