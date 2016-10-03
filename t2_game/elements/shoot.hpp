#ifndef shootH
#define shootH
#include <GLee.h>         // No need to link to GL/gl.h
#include "point3D.hpp"

class shoot {
private:
    point3D* position;
    GLfloat speedFactor;
    GLfloat timeToLive;
    GLfloat age;
    GLfloat xMove;
    GLfloat yMove;
    GLfloat zMove;
    void calculateMovement();
public:
    shoot(point3D* startPos){
        this->position = startPos;
        this->speedFactor = 1;
        this->age =  0;
        this->timeToLive = 500;
        this->xMove = 0.0f;
        this->yMove = 0.0f;
        this->zMove = 0.0f;
        this->calculateMovement();
    }
    void draw();
    bool isAlive();
};
#endif
