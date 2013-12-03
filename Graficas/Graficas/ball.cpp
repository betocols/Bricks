//
//  ball.cpp
//  Graficas
//
//  Created by Alberto Cols & Oriana Gomez on 29/11/13.
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
#include "ball.h"


Ball::Ball(){
    xpos = 0.0;
    ypos = -8.25;
    speed = 0.0;
    rot = 90.0;
    last = 0;
    
}     //Constructor

Ball::~Ball(){
}    //Destructor

void Ball::initBall(){
    xpos = 0.0;
    ypos = -8.25;
    speed = 0.0;
    rot = 90.0;
    last = 0;
}

void Ball::drawBall(float x, float y, float r){
    float radio = 0.20;
    
    glPushMatrix();

    glTranslated(xpos, ypos, 0.0);

    glBegin(GL_LINE_LOOP);


    glRotated(rot, 0.0, 0.0, 1.0);

    xpos += speed*cosf(rot*M_PI/180);
    ypos += speed*sinf(rot*M_PI/180);

    glTranslated(0.0, 1.0, 0.0);

    //If it goes out
    if (ypos <= -10) {
        initBall();
    }
    
    glColor3f(0.9, 0.6, 0.3);
    glBegin(GL_LINE_LOOP);
    for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {  // +1 para cerrar
        glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
    }
    glEnd();
    
    glPopMatrix();
}

float Ball::getSpeed(){
    return speed;
}

void Ball::increaseSpeed(){
    
    if (speed*1.1 > 0.161051) {
        printf("Ball speed at top: %f\n", speed);
        return;
    }

    speed *= 1.1;
    printf("Ball speed increased: %f\n", speed);
}

void Ball::resetSpeed() {
    speed = 0.1;
    printf("Ball speed reset: %f\n", speed);
}

float Ball::getY() {
    return ypos;
}

float Ball::getX() {
    return ypos;
}

float Ball::getR(){
    return rot;
}

void Ball::changeR(float r) {
    rot += r;
}

void Ball::move(int direction) {
    xpos += direction*speed*cosf(rot);
    ypos += direction*speed*sinf(rot);
}
                      
void Ball::boing(Platform plat) {
    //Besides checking the collition, it also checks that the last element that it crashed with
    //is different of the element that it is going to crash
    //Platform
    float splat = plat.getSize();
    float xplat = plat.getX();
    
    if (last != -1 && xpos < (xplat+splat) && xpos > (xplat-splat) && ypos < -8.3 && ypos > -8.9) {
        move(-1);
        if (xpos < xplat) {
            rot = 90 + ((xplat - xpos))*45;
            
        } else if (xpos > xplat)
            rot = (splat + 0.5 - (xpos - xplat))*45;
        else
            rot = 360-rot;
        
//        printf("dif= %f, size= %f , xpos= %f, plat: %f, rot %f:\n",dif, splat, xpos, xplat, rot);
        
        move(1);
        last = -1;
    }
    
    //Top
    if (ypos > 8.8 && last != -2) {
        move(-1);
        rot = 360 - rot;
        move(1);
        last = -2;
    }

    //Walls
    if ((xpos < -9.8 && last != -4) || (xpos > 9.8 && last != -3)) {
        move(-1);
        rot = 180 - rot;
        move(1);
        if (xpos > 0.0)
            last = -3;
        else
            last = -4;

    }
}