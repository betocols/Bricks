//
//  skeleton.cpp
//  Graficas
//
//  Created by Alberto Cols on 20/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//
#include <GL/glew.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include "skeleton.h"
#include <stdio.h>

Skeleton::Skeleton(){
    angle = 15.0;
    neck = 0.0;
    backUp = 0.0;
    backDown = 0.0;
    shoulderL = 0.0;
    shoulderR = 0.0;
    elbowL = 0.0;
    elbowR = 0.0;
    wristL = 0.0;
    wristR = 0.0;
    hipL = 0.0;
    hipR = 0.0;
    kneeL = 0.0;
    kneeR = 0.0;
    ankleL = 0.0;
    ankleR = 0.0;
    
}

Skeleton::~Skeleton(){
    
}

void Skeleton::stickMan(int side, float rot, int paint, int section){
    trunk(side, rot, paint, section);
    hip(side, rot, paint, section);
    
}

/************************** Upper Body **************************/
void Skeleton::trunk(int side, float rot, int paint, int section){
    glPushMatrix();
    
    if ((side == 6) && (section == 0)) {
        backUp += fmodf((angle*rot), 360.0);
    }
    glRotated(backUp, 0.0, 0.0, 1.0);
    
    cape();
    
    if (paint == 6) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //upTrunk
    glBegin(GL_LINES);
    glVertex3f(0.0, 3.5, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    
    drawS();
    
    if (paint == 6) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //trap
    glBegin(GL_LINES);
    glVertex3f(2.0, 3, 0.0);
    glVertex3f(-2.0, 3, 0.0);
    glEnd();
    
    arm(side, rot, paint, section);
    head(side, rot, paint, section);
    
    glPopMatrix();
}

void Skeleton::cape() {
    glPushMatrix();
    
    glColor4f(1.0, 0.0, 0.0, 0.2);
    glTranslated(0.0, 3.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-4.0, -10.0, 0.0);
    glVertex3f(4.0, -10.0, 0.0);
    glEnd();
    
    
    glPopMatrix();
}

void Skeleton::drawS(){
    
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor4f(1.0,1.0,0.0,1.0);
    
    glVertex3f(0.0, 2.6, 0.0);
    glVertex3f(0.0, 1.4, 0.0);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor4f(1.0,0.0,0.0,1.0);
    
    glVertex3f(0.05, 2.5, 0.0);
    glVertex3f(0.05, 2.3, 0.0);
    
    glVertex3f(0.05, 2.5, 0.0);
    glVertex3f(-0.05, 2.5, 0.0);
    
    glVertex3f(-0.05, 2.5, 0.0);
    glVertex3f(-0.05, 2.0, 0.0);
    
    glVertex3f(0.05, 2.0, 0.0);
    glVertex3f(-0.05, 2.0, 0.0);
    
    glVertex3f(0.05, 2.0, 0.0);
    glVertex3f(0.05, 1.5, 0.0);
    
    glVertex3f(0.05, 1.5, 0.0);
    glVertex3f(-0.05, 1.5, 0.0);
    
    glVertex3f(-0.05, 1.5, 0.0);
    glVertex3f(-0.05, 1.8, 0.0);
    
    glEnd();
    
    glLineWidth(10.0);
}
void Skeleton::head(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(0,3.5,0);
    
    if ((side == 5) && (section == 0)) {
        neck += fmodf((angle*rot), 360.0);
    }
    glRotated(neck, 0.0, 0.0, 1.0);
    
    if ((paint == 5) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.94, 0.82, 0.51,1.0);
    }
    
    
    double radio, PI;
    radio = 1.0;
    PI = 3.1416;
    
    glTranslated(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (double i = 0; i < 2 * PI; i += PI / 12) {  // +1 para cerrar
        glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
    }
    glEnd();
    
    //Eyes
    glBegin(GL_POINTS);
    glColor4f(0.0, 0.2, 1.0, 1.0);
    glVertex3f(-0.3, 0.3, 0.0);
    glVertex3f(0.3, 0.3, 0.0);
    glEnd();
    
    
    //Neck
    glBegin(GL_POINTS);
    glColor4f(1.0, 0.3, 0.0,1);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();
    
    glPopMatrix();
}

void Skeleton::arm(int side, float rot, int paint, int section){
    
    /**** Left Arm ****/
    glPushMatrix();
    glTranslated(-2.0, 3.0, 0.0);
    
    if ((side == 3) && (section == 0)) {
        shoulderL += fmodf((angle*rot), 360.0);
    }
    glRotated(shoulderL, 0.0, 0.0, 1.0);
    
    if ((paint == 3) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(-2.0, 0.0, 0.0);
    glVertex3f(-0.0, 0.0, 0.0);
    glEnd();
    
    subarmL(side, rot, paint, section);
    
    //ShoulderL
    articulation();
    glPopMatrix();
    
    //**** Right Arm ****/
    glPushMatrix();
    glTranslated(2.0, 3.0, 0.0);
    
    if ((side == 4) && (section == 0)) {
        shoulderR += fmodf((angle*rot), 360.0);
    }
    glRotated(shoulderR, 0.0, 0.0, 1.0);
    
    if ((paint == 4) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    
    //ShoulderR
    articulation();
    
    subarmR(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::subarmL(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(-2.0, 0.0, 0.0);
    
    if ((side == 3) && (section == 1)) {
        elbowL += fmodf((angle*rot), 360.0);
    }
    glRotated(elbowL, 0.0, 0.0, 1.0);
    
    if ((paint == 3) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0, 0.0);
    glVertex3f(-2.0, 0, 0.0);
    glEnd();
    
    //ElbowL
    articulation();
    
    handL(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::subarmR(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(2.0, 0.0, 0.0);
    
    if ((side == 4) && (section == 1)) {
        elbowR += fmodf((angle*rot), 360.0);
    }
    glRotated(elbowR, 0.0, 0.0, 1.0);
    
    if ((paint == 4) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glEnd();
    
    //ElbowR
    articulation();
    
    handR(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::handL(int side, float rot, int paint, int section){
    glPushMatrix();
    
    glTranslated(-2.0, 0.0, 0.0);
    
    if ((side == 3) && (section == 2)) {
        wristL += fmodf((angle*rot), 360.0);
    }
    glRotated(wristL, 0.0, 0.0, 1.0);
    
    if ((paint == 3) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.94, 0.82, 0.51,1.0);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    //WristL
    articulation();
    glPopMatrix();
}

void Skeleton::handR(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(2.0, 0.0, 0.0);
    
    if ((side == 4) && (section == 2)) {
        wristR += fmodf((angle*rot), 360.0);
    }
    glRotated(wristR, 0.0, 0.0, 1.0);
    
    if ((paint == 4) || (paint == 6)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.94, 0.82, 0.51,1.0);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    
    
    //WristR
    articulation();
    
    glPopMatrix();
}


/************************** Down Body **************************/
void Skeleton::hip(int side, float rot, int paint, int section){
    glPushMatrix();
    
    if ((side == 7) && (section == 0)) {
        backDown += fmodf((angle*rot), 360.0);
    }
    glRotated(backDown, 0.0, 0.0, 1.0);
    
    if (paint == 7) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(1.0, 0.0, 0.0,0.9);
    }
    
    //downTrunk
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -2, 0.0);
    glEnd();
    
    //hip
    glBegin(GL_LINES);
    glVertex3f(-1.0, -2, 0.0);
    glVertex3f(1.0, -2, 0.0);
    glEnd();
    
    //BreakPoint
    articulation();
    
    legL(side, rot, paint, section);
    legR(side, rot, paint, section);
    
    glPopMatrix();
}

void Skeleton::legL(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(-1.0, -2.0, 0.0);
    
    if ((side == 1) && (section == 0)) {
        hipL += fmodf((angle*rot), 360.0);
    }
    glRotated(hipL, 0.0, 0.0, 1.0);
    
    if ((paint == 1) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0, 0.0);
    glVertex3f(0.0, -3, 0.0);
    glEnd();
    
    //HipL
    articulation();
    
    sublegL(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::legR(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(1.0, -2.0, 0.0);
    
    if ((side == 2) && (section == 0)) {
        hipR += fmodf((angle*rot), 360.0);
    }
    glRotated(hipR, 0.0, 0.0, 1.0);
    
    if ((paint == 2) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(0.0, 0.0, 1.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0, 0.0);
    glVertex3f(0.0, -3, 0.0);
    glEnd();
    
    //HipR
    articulation();
    
    sublegR(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::sublegL(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(0.0, -3.0, 0.0);
    
    if ((side == 1) && (section == 1)) {
        kneeL += fmodf((angle*rot), 360.0);
    }
    glRotated(kneeL, 0.0, 0.0, 1.0);
    
    if ((paint == 1) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(1.0, 0.0, 0.0,0.9);
    }
    
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -3.0, 0.0);
    glEnd();
    
    //KneeL
    articulation();
    
    footL(side, rot, paint, section);
    glPopMatrix();
}

void Skeleton::sublegR(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(0.0, -3.0, 0.0);
    
    if ((side == 2) && (section == 1)) {
        kneeR += fmodf((angle*rot), 360.0);
    }
    glRotated(kneeR, 0.0, 0.0, 1.0);
    
    if ((paint == 2) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(1.0, 0.0, 0.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, -3.0, 0.0);
    glEnd();
    
    //KneeR
    articulation();
    
    footR(side, rot, paint, section);
    
    glPopMatrix();
}

void Skeleton::footL(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(0.0, -3.0, 0.0);
    
    if ((side == 1) && (section == 2)) {
        ankleL += fmodf((angle*rot), 360.0);
    }
    glRotated(ankleL, 0.0, 0.0, 1.0);
    
    if ((paint == 1) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(1.0, 0.0, 0.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(-1.0, 0.0, 0.0);
    glEnd();
    
    //AnkleL
    articulation();
    glPopMatrix();
}

void Skeleton::footR(int side, float rot, int paint, int section){
    glPushMatrix();
    glTranslated(0.0, -3.0, 0.0);
    
    if ((side == 2) && (section == 2)) {
        ankleR += fmodf((angle*rot), 360.0);
    }
    glRotated(ankleR, 0.0, 0.0, 1.0);
    
    if ((paint == 2) || (paint == 7)) {
        glColor4f(1.0,1.0,1.0,1.0);
    } else {
        glColor4f(1.0, 0.0, 0.0,0.9);
    }
    
    //bone
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    
    //AnkleR
    articulation();
    
    glPopMatrix();
}

//Extra
void Skeleton::articulation(){
    glBegin(GL_POINTS);
    glColor4f(1.0, 0.3, 0.0,1);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    
}