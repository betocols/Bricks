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
    bonus = 1.0;
    life = 3;
}

Platform::~Platform() {
    
}

int Platform::getBonus() {
    return bonus;
}

void Platform::changeBonus(float b) {
    float left, right;
    //Increases the size of the platform
    if (b == 1.0)
        bonus = 1.0;
    //Takes the size of the platform back to normal
    else {
        bonus *= 1.05;
        
        //Bonus top is 1.05^5
        if (bonus > 1.27681)
            bonus = 1.27681;
        
        //If the platform increases it size at one border,
        //moves the center so it doesnt pass the border
        left = xpos - bonus;
        right = xpos + bonus;
        if (left <= -10.0)
            xpos = -10.0 + bonus;
        else if (right >= 10.0)
            xpos = 10.0 - bonus;
    }
    
    printf("bonus %f, b %f\n", bonus, b);
}

int Platform::getX() {
    return xpos;
}

void Platform::moveX(float x) {
    float t = xpos + x;
    float left = t - bonus;
    float right = t + bonus;

    //If the platform is inside the boundaries of the field
    if ((t >= -10.0 + bonus) && (t <= 10.0 - bonus)) {
        xpos += x;
    }

    //If it tries to go outside the boundaries, it takes the platform back
    if (left < -10.0) {
        xpos = -10.0 + bonus;

    } else if (right > 10.0) {
        xpos = 10.0 - bonus;

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
    glVertex3f(xpos-bonus, -9.0, 0.0);
    glVertex3f(xpos+bonus, -9.0, 0.0);
    
    glVertex3f(xpos-bonus, -9.0, 0.0);
    glVertex3f(xpos-bonus, -8.5, 0.0);
    
    glVertex3f(xpos+bonus, -9.0, 0.0);
    glVertex3f(xpos+bonus, -8.5, 0.0);
    
    glVertex3f(xpos-bonus, -8.5, 0.0);
    glVertex3f(xpos+bonus, -8.5, 0.0);
    
    glEnd();
    //End Platform

}



