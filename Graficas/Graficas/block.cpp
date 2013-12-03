//
//  block.cpp
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
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
#include "block.h"


Block::Block(){
}

Block::~Block(){    
}

void Block::initBlock(int n, float x, float y, int t, int b){
    num = n;
    xpos = x;
    ypos = y;
    type = t;
    

    if (type == 0)      //Normal
        life = 1;
    else                //Special
        life = 2;
    
    if (b == 0)         //Normal
        bonus = 0;
    else if (b == 1)    //Size
        bonus = 1;
    else if (b == 2)    //Speed
        bonus = 2;
        
}

void Block::drawUndamaged() {
    
    glBegin(GL_LINES);
    //bottomline
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    //leftline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    //rightline
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    //topline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glEnd();

}

void Block::drawDamaged() {
    
    glBegin(GL_LINES);
    //////////////LEFT
    //bottomlineLeft
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    glVertex3f(xpos-0.2, ypos-0.25, 0.0);

    //bottomCenterCrackLeft
    glVertex3f(xpos-0.35, ypos-0.05, 0.0);
    glVertex3f(xpos-0.2, ypos-0.25, 0.0);

    //centerCenterCrackLeft
    glVertex3f(xpos-0.35, ypos-0.05, 0.0);
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);

    //topCenterCrackLeft
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);
    glVertex3f(xpos+0.0, ypos+0.25, 0.0);
    
    //leftCenterCrackBottom
    glVertex3f(xpos-1.0, ypos-0.1, 0.0);
    glVertex3f(xpos-0.3, ypos-0.05, 0.0);
    
    //leftCenterCrackTop
    glVertex3f(xpos-1.0, ypos+0.1, 0.0);
    glVertex3f(xpos+0.1, ypos+0.08, 0.0);

    //leftline
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos-1.0, ypos-0.25, 0.0);
    
    //toplineLeft
    glVertex3f(xpos-1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+0.0, ypos+0.25, 0.0);
    
    //////////////RIGHT
    //bottomlineRight
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+0.0, ypos-0.25, 0.0);

    //bottomCenterCrakRight
    glVertex3f(xpos+0.0, ypos-0.25, 0.0);
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    
    //centerCenterCrakRight
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);
    
    //centerTopCrackRight
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);
    glVertex3f(xpos+0.25, ypos+0.25, 0.0);
    
    //rightCenterCrackBottom
    glVertex3f(xpos+1.0, ypos-0.04, 0.0);
    glVertex3f(xpos-0.2, ypos-0.1, 0.0);
    
    //rightCenterCrackTop
    glVertex3f(xpos+1.0, ypos+0.1, 0.0);
    glVertex3f(xpos+0.4, ypos+0.08, 0.0);

    //bottomlineRight
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    glVertex3f(xpos+0.1, ypos-0.25, 0.0);
    
    //rightline
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+1.0, ypos-0.25, 0.0);
    
    //toplineRight
    glVertex3f(xpos+1.0, ypos+0.25, 0.0);
    glVertex3f(xpos+0.25, ypos+0.25, 0.0);

    glEnd();
    
}

/* Returns:
 *  -1 = if block is already destroyed and it doesnt have a bonus
 *  -2 = if
 *
 *
 *
 *
 */
int Block::drawBlock(){
    if (life < 0) {
        float radio = 0.35;
        float radio2 = 0.15;
        glPointSize(10.0);
        if (bonus == 1) {   //Platform size
            glColor3f(0.9, 0.6, 0.3);
            glPushMatrix();
            glTranslated(xpos, ypos -= 0.05, 0.0);
            
            glBegin(GL_LINE_LOOP);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {  // +1 para cerrar
                glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
            }
            glEnd();
            
            glPushMatrix();
            glTranslated(0.09, 0.0, 0.0);
            
            glBegin(GL_LINES);
            glVertex3f(-0.3, 0.0, 0.0);
            glVertex3f(-0.16, 0.0, 0.0);
            glVertex3f(-0.28, 0.15, 0.0);
            glVertex3f(0.0, 0.15, 0.0);
            glVertex3f(-0.28, -0.15, 0.0);
            glVertex3f(0.0, -0.15, 0.0);
            glEnd();
            
            glBegin(GL_LINE_LOOP);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {  // +1 para cerrar
                glVertex3f( cos(i) * radio2, sin(i) * radio2, 0.0 );
            }
            glEnd();
            glPopMatrix();
            
            glPopMatrix();
            
        } else if (bonus == 2) {    //Ball speed
            glColor4f(0.0, 0.0, 1.0, 1.0);
            glPushMatrix();
            glTranslated(xpos, ypos -= 0.05, 0.0);
            
            glBegin(GL_LINE_LOOP);
            for (double i = 0; i < 2 * M_PI; i += M_PI / 12) {  // +1 para cerrar
                glVertex3f( cos(i) * radio, sin(i) * radio, 0.0 );
            }
            glEnd();
            
            glBegin(GL_LINES);
            glVertex3f(0.28, 0.1, 0.0);
            glVertex3f(-0.28, 0.1, 0.0);
            glVertex3f(-0.28, 0.1, 0.0);
            glVertex3f(-0.28, -0.1, 0.0);
            glVertex3f(0.28, 0.1, 0.0);
            glVertex3f(0.28, -0.1, 0.0);
            glVertex3f(0.28, -0.1, 0.0);
            glVertex3f(-0.28, -0.1, 0.0);

            glColor4f(0.0, 0.0, 1.0, 1.0);
            glVertex3f(-0.15, 0.1, 0.0);
            glVertex3f(0.15, 0.1, 0.0);
            glVertex3f(-0.15, 0.1, 0.0);
            glVertex3f(-0.15, -0.1, 0.0);
            glVertex3f(0.15, 0.1, 0.0);
            glVertex3f(0.15, -0.1, 0.0);
            glVertex3f(0.15, -0.1, 0.0);
            glVertex3f(-0.15, -0.1, 0.0);
            glEnd();
            
            glPopMatrix();
        }
        return -1;
    }
    
    if (life == 0) {
		if (type == 1)
            return -2;
        return 0;
    }
    
    //Block is alive and is normal
    if (type == 0) {
        glColor4f(1.0, 1.0, 1.0, 1.0);
        drawUndamaged();
    //Block is alive and type is special
    } else {
        glColor4f(1.0, 0.0, 0.0, 1.0);
        if (life == 2)
            drawUndamaged();
        else
            drawDamaged();
    }
    
    return life;
}

float Block::getX() {
   return xpos;
}

float Block::getY() {
    return ypos;
}

int Block::getBonus() {
    return bonus;
}

void Block::setBonus(int b) {
    bonus = b;
}

int Block::getLife() {
    return life;
}

void Block::changeLife(int l) {
    life--;
}


