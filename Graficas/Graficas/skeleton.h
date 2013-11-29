//
//  skeleton.h
//  Graficas
//
//  Created by Alberto Cols on 20/11/13.
//  Copyright (c) 2013 Alberto Cols. All rights reserved.
//

class Skeleton {
    
public:
    Skeleton();  //Constructor
    ~Skeleton(); //Destructor
    
    //Draws the stickMan
    void stickMan(int side, float rot, int paint, int section);
    
private:
    float angle;
    float neck;
    float backUp;
    float backDown;
    float shoulderL;
    float shoulderR;
    float elbowL;
    float elbowR;
    float wristL;
    float wristR;
    float hipL;
    float hipR;
    float kneeL;
    float kneeR;
    float ankleL;
    float ankleR;
    
    //UpperBody
    //Draws the trunk
    void trunk(int side, float rot, int paint, int section);
    //Draws the head
    void head(int side, float rot, int paint, int section);
    //Draws the arm
    void arm(int side, float rot, int paint, int section);
    //Draws the left subarm
    void subarmL(int side, float rot, int paint, int section);
    //Draws the right subarm
    void subarmR(int side, float rot, int paint, int section);
    //Draws the left hand
    void handL(int side, float rot, int paint, int section);
    //Draws the right hand
    void handR(int side, float rot, int paint, int section);
    
    //DownBody
    //Draws the hip
    void hip(int side, float rot, int paint, int section);
    //Draws the left leg
    void legL(int side, float rot, int paint, int section);
    //Draws the right leg
    void legR(int side, float rot, int paint, int section);
    //Draws the left subleg
    void sublegL(int side, float rot, int paint, int section);
    //Draws the right subleg
    void sublegR(int side, float rot, int paint, int section);
    //Draws the left foot
    void footL(int side, float rot, int paint, int section);
    //Draws the right foot
    void footR(int side, float rot, int paint, int section);
    
    //Extra
    //Draw articulation
    void articulation();
    //Draw SUPER-CAPE
    void cape();
    //Draw S
    void drawS();
    
};

