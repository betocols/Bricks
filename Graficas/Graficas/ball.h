//
//  ball.h
//  Graficas
//
//  Created by Alberto Cols & Oriana Gomez on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

#include <iostream>
#include "platform.h"
#include "block.h"

class Ball {
    float xpos;
    float ypos;
    float rot;
    float speed;
    int last;
    int stop;
    
public:
    
    Ball();     //Constructor
    ~Ball();    //Destructor

    void initBall();
    int drawBall(float x, float y, float r);

    float getSpeed();
    void increaseSpeed();
    void resetSpeed();
    
    void setStop(int s);
    int getStop();
    
    float getY();
    float getX();
    
    void changeR(float r);
    float getR();
    
    void move(int direction);
    void boing(Platform plat, Block blocks[35]);
    void drawDirection();
};