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
    
    void drawBall(float x, float y);
    float getSpeed();
    void setSpeed(int reset);
    
};