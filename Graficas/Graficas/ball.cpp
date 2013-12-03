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
    ypos = -8.29;
    speed = 0.0;
    rot = 90.0;
    last = 0;
    stop = 0;
    
}     //Constructor

Ball::~Ball(){
}    //Destructor

void Ball::initBall(){
    xpos = 0.0;
    ypos = -8.29;
    speed = 0.0;
    rot = 90.0;
    last = 0;
    stop = 0;
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

void Ball::drawDirection() {
    glPushMatrix();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTranslated(xpos, ypos, 0.0);
    glRotated(rot-90, 0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 1.2, 0.0);
    glVertex3f(0.0, 0.4, 0.0);
    glVertex3f(0.0, 1.2, 0.0);
    glVertex3f(-0.2, 1, 0.0);
    glVertex3f(0.0, 1.2, 0.0);
    glVertex3f(0.2, 1, 0.0);
    glEnd();
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

void Ball::setStop(int s) {
    stop = s;
}

int Ball::getStop() {
    return stop;
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
    float result = rot + r;
    
    if (result < 30.0 || result > 150.0)
        return;
    
    rot = result;
}

void Ball::move(int direction) {
    xpos += direction*speed*cosf(rot);
    ypos += direction*speed*sinf(rot);
}
                      
void Ball::boing(Platform plat, Block blocks[35]) {
    //Besides checking the collition, it also checks that the last element that it crashed with
    //is different of the element that it is going to crash
    //Platform
    float splat = plat.getSize()+0.25;
    float xplat = plat.getX();
    
    if (last != -1 && xpos < (xplat+splat) && xpos > (xplat-splat) && ypos < -8.3 && ypos > -8.5) {
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
    
    //Blocks
    float top, right, bottom, left;
    float blr, bll, blt, blb, cx, cy;
    for (int k = 0; k < 35; k++) {
        if ((last != k) && (blocks[k].getLife() > 0)) {
            //Borders of the ball
            right = xpos + 0.2;
            left = xpos - 0.2;
            top = ypos + 0.2;
            bottom = ypos - 0.2;
            
            //Borders of the block
            cx = blocks[k].getX();
            blr = cx + 1.2;
            bll = cx - 1.2;
            cy = blocks[k].getY();
            blt = cy + 0.27;
            blb = cy - 0.27;
            
            //Top and Bottom
            if (((top >= blb && top <= cy) || (bottom <= blt && bottom >= cy))  && (xpos >= bll && xpos < blr)) {
                move(-1);
                rot = 360 - rot;
                move(1);
                blocks[k].changeLife(-1);
                last = k;
                continue;
            }

            //Walls
            if ((bottom <= blt && top >= blb) &&  ((right >= bll && right <= cx) || (left <= blr && left >= cx))) {
                move(-1);
                rot = 180 - rot;
                move(1);
                blocks[k].changeLife(-1);
                last = k;
            }

        }
    }
}