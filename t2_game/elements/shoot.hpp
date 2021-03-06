#ifndef shootH
#define shootH
#include <GLee.h>         // No need to link to GL/gl.h
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "baseElement.hpp"
#include "modelObj.hpp"
#include "asteroid.hpp"

class shoot : public baseElement{
private:
    modelObj* oModel;
    GLfloat timeToLive;
    GLfloat age;
    GLfloat damage;
public:
    shoot(point3D* startPos,colorRgb* bColor,GLfloat d, GLfloat s):baseElement(startPos, bColor, s){
        this->age =  0;
        this->timeToLive = 500;
        this->oModel = new modelObj(bColor,false);
        this->damage = d;
        this->calculateMovementForward();
    }
    shoot(point3D* startPos,modelObj* mObj,GLfloat d, GLfloat s):shoot(startPos,mObj->getColor(),d,s){
        this->oModel = mObj;
    }
    bool hitAsteroid(asteroid* a);
    void draw();
    bool isAlive();
};
#endif
