//
//  platform.h
//  Graficas
//
//  Created by Alberto Cols on 29/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

class Platform {
    
    int bonus;      //0 = Normal platform / 1 = Bonus platform size / 2 = Bonus platform speed
    int life;       //Remaining life
    float xpos;     //X position
    
public:
    Platform();  //Constructor
    ~Platform(); //Destructor
    
    //Draws the block
    void drawPlatform();
    int getBonus();
    void setBonus(int b);
    int getX();
    void moveX(float x);
    
private:

};
