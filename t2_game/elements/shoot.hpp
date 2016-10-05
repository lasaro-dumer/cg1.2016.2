#ifndef shootH
#define shootH
#include <GLee.h>         // No need to link to GL/gl.h
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "baseElement.hpp"

class shoot : public baseElement{
private:
    GLfloat timeToLive;
    GLfloat age;
public:
    shoot(point3D* startPos,colorRgb* bColor):baseElement(startPos, bColor,1){
        this->age =  0;
        this->timeToLive = 500;
        this->calculateMovementForward();
    }
    void draw();
    bool isAlive();
};
#endif
