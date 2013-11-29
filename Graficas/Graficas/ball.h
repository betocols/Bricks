//
//  ball.h
//  Graficas
//
//  Created by Alberto Cols & Oriana Gomez on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

#include <iostream>

class Ball {
    float xpos;
    float ypos;
    float rot;
    float speed;
    
public:
    
    Ball();     //Constructor
    ~Ball();    //Destructor
    
    void drawBall(float x, float y, float r);
    float getSpeed();
    void changeSpeed(int s);
    
    float getY();
    float getX();
    
    void changeR(float r);
    float getR();
};