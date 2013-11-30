//
//  block.h
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

class Block {

    int type;       //0 = Normal block / 0 != Special block
    int bonus;      //0 = Normal block / 1 = Bonus block size / 2 = Bonus block speed
    int life;       //Remaining life
    float xpos;     //X position
    float ypos;     //Y position

public:
    Block();  //Constructor
    ~Block(); //Destructor
    
    //Draws the block
    void drawBlock();
    void initBlock(float x, float y, int t, int b);
    float getX();
	void boom();
    void changeLife(int l);
    int getLife();

private:
    void drawUndamaged();
    void drawDamaged();
    
    
    
};
