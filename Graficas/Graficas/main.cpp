//
//  main.cpp
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//
#include <GL/glew.h>
#include <ctime>
#ifdef __APPLE__
#include <GLUT/glut.h>
#elif _WIN32
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "block.h"
#include "platform.h"
#include "ball.h"

using namespace std;

#define DEF_floorGridScale  1.0
#define DEF_floorGridXSteps 10.0
#define DEF_floorGridZSteps 10.0
Block blocks[35];                   //Array of blocks
int special[7];                     //Array to obtain the number of the especial blocks
int bonus[5];                       //Array to obtain the number of the bonus blocks
Platform p;
Ball b;
int i = 0;

void changeViewport(int w, int h) {
    
    float aspectratio;
    
    if (h==0)
        h=1;
    
    
    glViewport(0,0,w,h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    
    aspectratio = (float) w / (float) h;
    
    if (w<=h) {
        
        glOrtho(-10.0,10.0,-10.0/aspectratio,10.0/aspectratio,1.0,50.0);
        
    }else {
        
        glOrtho(-10.0*aspectratio,10.0*aspectratio,-10.0,10.0,1.0,50.0);
        
    }
    
    
    glMatrixMode (GL_MODELVIEW);
}

//Draws the border of the game
void gameset() {
    //GameBorder
    glBegin(GL_LINES);
    glColor4f(0.0, 1.0, 0.0, 1.0);
    //Left Column
    glVertex3f(-10.0, -9.0, 0.0);
    glVertex3f(-10.5, -9.0, 0.0);
    
    glVertex3f(-10.0, -9.0, 0.0);
    glVertex3f(-10.0, 9.0, 0.0);
    
    glVertex3f(-10.5, -9.0, 0.0);
    glVertex3f(-10.5, 9.5, 0.0);
    
    glVertex3f(-10.0, 9.0, 0.0);
    glVertex3f(-10.5, 9.5, 0.0);
    
    //Top Column
    glVertex3f(-10.5, 9.5, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(-10.0, 9.0, 0.0);
    glVertex3f(10.0, 9.0, 0.0);
    
    //Right Column
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.0, 9.0, 0.0);
    
    glVertex3f(10.0, 9.0, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(10.5, -9.0, 0.0);
    glVertex3f(10.5, 9.5, 0.0);
    
    glVertex3f(10.0, -9.0, 0.0);
    glVertex3f(10.5, -9.0, 0.0);
    
    glEnd();
    //End GameBorder
    

}

//Fills the special array with the number of the blocks that are special and that have bonus
void initRands(){
    int randNum;
    int j = 1, k;

    
    //Sets seed to get random number every time
    srand ( (unsigned)time(NULL));
    //Assign the first random value
    special[0] = rand()% 34;

    while (j < 7){
        randNum = rand()% 34;
        
        for (k = 0; k < j; k++) {
            if (special[k] == randNum)
                break;
        }

        if (k == j){
            special[j] = randNum;
            j++;
        }
        
        
    }
    
    j = 0;
    bonus[0] = rand()% 34;
    while (j < 5){
        randNum = rand()% 34;
        
        for (k = 0; k < j; k++) {
            if (bonus[k] == randNum)
                break;
        }
        
        if (k == j){
            bonus[j] = randNum;
            j++;
        }
        
        
    }
}

//Determines wether the number is special or not
int isSpe(int e){
    for(int j = 0; j < 7; j++)
        if (special[j] == e)
            return 1;
    
    return 0;
}

//Determines wether the number is special or not
int isBon(int e){
    int r;
    int j;
    
    for(j = 0; j < 5; j++)
        if (bonus[j] == e)
            break;
    
    if (j == 5)
        return 0;
    
    r = bonus[j] % 2;
    if (r == 0)
        return r + 2;
    else if (r == 1)
        return r;
    
    return 0;
}

void render(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity ();
    gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    
    //Suaviza las lineas
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_LINE_SMOOTH );
    glEnable( GL_POINT_SMOOTH );
    
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    
    
    gameset();
    
    p.drawPlatform();
    
    for(i = 0; i < 35; i++) {
        blocks[i].drawBlock();
    }
    
    b.drawBall(0.0, 0.0, 0.0);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    switch(key)
    {
//        case GLUT_KEY_LEFT:
        case 'j':
        case 'J':
            p.moveX(-0.5);
            break;
//        case GLUT_KEY_RIGHT:
        case 'l':
        case 'L':
            p.moveX(0.5);
            break;
            //        case GLUT_KEY_RIGHT:
        case 'a':
        case 'A':
            b.changeR(-45.0);
            break;
            //        case GLUT_KEY_RIGHT:
        case 'd':
        case 'D':
            b.changeR(45.0);
            break;
        case 'b':
            blocks[0].changeLife(-1);
            break;
        case 27:   // escape
            exit(0);
            break;
            
        default:
            break;
    }
    
    render();
}

void TimeEvent(int te)
{
    
    b.drawBall(0.0, 0.1, 0.0);
	glutPostRedisplay();
	glutTimerFunc(100, TimeEvent, 1);

}

int main (int argc, char** argv) {
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    
    glutInitWindowSize(900,700);
    
    glutCreateWindow("Proyecto 2");
    
    glutReshapeFunc(changeViewport);
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    }
    
    //Gets the special blocks
    initRands();
    //Blocks Initializing
    for (float x = -7.5; x <= 7.5; x += 2.5) {
        for (float y = 6.0; y > 1.0; y -= 1.0) {
            blocks[i].initBlock(x, y, isSpe(i), isBon(i));
            i++;
        }
    }
    
    glutTimerFunc( 10, TimeEvent, 1);
    glutMainLoop();
    return 0;
    
}