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

void Ball::initBall(){
    xpos = 0.0;
    ypos = -8.25;
    speed = 0.1;
    rot = 90.0;
}

void Ball::drawBall(float x, float y, float r){
    double radio;
    radio = 0.20;
    
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
    speed = 0.3;
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
    //TOPE Y FONDO
    if (ypos > 8.8 || ypos < -9.0) {
      move(-1);
      rot = 360 - rot;
      move(1);
    }

    //LADOS
    if (xpos < -9.8 || xpos > 9.8) {
        printf("Antes move(-1)   %f,",xpos);
        move(-1);
        printf("Despues move(-1)   %f, ",xpos);
        rot = 180 - rot;
        printf("Antes move(1)   %f, ",xpos);
        move(1);
        printf("Despues move(1)   %f\n\n",xpos);
    }

    // //BARRA IZQUIERDA
    // if (xpos < -10.0 && xpos > -10.5 && ypos > -9.0 && ypos < 9.0) {
    //     move(-1);
    //     rot = (-PI/2) + ((PI/8) + ((ypos - plat[0].getY())/6)*(PI - PI/4));

    //     if (ypos - plat[0].getY() < 1 || ypos - plat[0].getY() > 5)
    //         rapida = 2;
    //     else 
    //         rapida = 1; 
    //     move(1); 
    // } 

    // //BARRA DERECHA
    // if (xpos < 10.0 && xpos > 10.5 && ypos > plat[0].getY() && ypos < 9.0) { 
    //     move(-1); 
    //     rot = (-PI/2) - ((PI/8) + ((ypos - plat[0].getY())/6)*(PI - PI/4)); 

    //     if (ypos - plat[0].getY() < 1 || ypos - plat[0].getY() > 5) 
    //         rapida = 2; 
    //     else 
    //         rapida = 1; 
    //     move(1); 
    // } 
}