//
//  block.h
//  Graficas
//
//  Created by Alberto Cols and Oriana Gomez on 28/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

class Block {
    
    int num;        //Id of the block
    int type;       //0 = Normal block / 0 != Special block
    int bonus;      //0 = Normal block / 1 = Bonus platform size / 2 = Bonus ball speed // 3 = Extra life
    int life;       //Remaining life
    float xpos;     //X position
    float ypos;     //Y position

public:
    Block();  //Constructor
    ~Block(); //Destructor
    
    //Draws the block
    int drawBlock();
    void initBlock(int num, float x, float y, int t, int b);
    float getX();
    float getY();
    int getBonus();
    void setBonus(int b);
    void changeLife(int l);
    int getLife();
    
private:
    void drawUndamaged();
    void drawDamaged();

    
};
