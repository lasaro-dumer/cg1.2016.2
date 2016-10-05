#ifndef baseElementH
#define baseElementH
#include <GLee.h>
#include "point3D.hpp"
#include "colorRgb.hpp"

class baseElement {
protected:
    point3D* position;
    colorRgb* color;
    GLfloat speedFactor;
    GLfloat xMove;
    GLfloat yMove;
    GLfloat zMove;
    void calculateMovementForward();
public:
    baseElement (point3D* pos, colorRgb* clr,GLfloat spd){
        this->position = pos;
        this->color = clr;
        this->speedFactor = spd;
        this->xMove = 0.0f;
        this->yMove = 0.0f;
        this->zMove = 0.0f;
    }
    baseElement(point3D* pos):baseElement(pos,new colorRgb(255,255,255),0){};
    void setSpeed(GLfloat value){
        this->speedFactor = value;
        this->calculateMovementForward();
    }
    void beforeDraw();
    virtual void draw(){}
    void afterDraw();
};

#endif
