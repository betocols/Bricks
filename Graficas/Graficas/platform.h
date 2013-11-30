//
//  platform.h
//  Graficas
//
//  Created by Alberto Cols on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

class Platform {
    
    float size;      //1.0 = Normal platform
    int life;       //Remaining life
    float xpos;     //X position
    
public:
    Platform();  //Constructor
    ~Platform(); //Destructor
    
    int getSize();
    void changeSize(float b);
    
    int getX();
    void moveX(float x);
    
    int getLife();
    void changeLife(int l);
    
    //Draws the block
    void drawPlatform();
    
private:
    
};
