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
#include "ball.h"
#include <math.h>


Ball::Ball(){
    xpos = 0.0;
    ypos = -8.25;
    speed = 0.1;
    rot = 90.0;
    
}     //Constructor

Ball::~Ball(){
}    //Destructor

void Ball::drawBall(float x, float y, float r){
    double radio, PI;
    radio = 0.24;
    PI = 3.1416;
    
    glPushMatrix();

    glTranslated(xpos, ypos, 0.0);

    glBegin(GL_LINE_LOOP);


    glRotated(rot, 0.0, 0.0, 1.0);

    xpos += speed*cosf(rot*PI/180);
    ypos += speed*sinf(rot*PI/180);

    glTranslated(0.0, 1.0, 0.0);
    
    glBegin(GL_LINE_LOOP);
    for (double i = 0; i < 2 * PI; i += PI / 12) {  // +1 para cerrar
        glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
    }
    glEnd();
    
    glPopMatrix();
}

float Ball::getSpeed(){
    return speed;
}

void Ball::changeSpeed(float s){
    
    //Reset speed
    if (s == 1.0)
        speed = 0.1;
    //Gets speed bonus
    else {
        if (speed*1.1 > 0.161052)
            return;
        speed *= 1.1;
    }
    
    printf("speed: %f\n", speed);
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


