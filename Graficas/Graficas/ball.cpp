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
    ypos = -8.5;
    speed = 1.0;
    rot = 0.0;
    
}     //Constructor
Ball::~Ball(){
}    //Destructor

void Ball::drawBall(float x, float y){

    double radio, PI;
    radio = 0.24;
    PI = 3.1416;
    
    glBegin(GL_LINE_LOOP);
    for (double i = 0; i < 2 * PI; i += PI / 12) {  // +1 para cerrar
        glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
    }
    glEnd();
}

float Ball::getSpeed(){
    return speed;
}

void Ball::setSpeed(int reset){

    if (reset == 1)
        speed = 1.0;
    else if (reset == 0)
        speed *= 1.10;
}