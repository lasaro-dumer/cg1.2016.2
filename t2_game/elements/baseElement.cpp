#include <GLee.h>
#include <math.h>
#include <iostream>
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "baseElement.hpp"
#include "../util/smmath.hpp"

void baseElement::calculateMovementForward(){
    // Control X-Axis movement
    this->xMove = 0.0f;
    this->yMove = 0.0f;
    this->zMove = 0.0f;
    float pitchFactor = cos(toRads(this->position->getXRot()));
    this->xMove += ( this->speedFactor * float(sin(toRads(this->position->getYRot()))) ) * pitchFactor;
    // Control Y-Axis movement
    this->yMove += this->speedFactor * float(sin(toRads(this->position->getXRot()))) * -1.0f;
    // Control Z-Axis movement
    float yawFactor = float(cos(toRads(this->position->getXRot())));
    this->zMove += ( this->speedFactor * float(cos(toRads(this->position->getYRot()))) * -1.0f ) * yawFactor;
    // X Speed cap
    if (this->xMove > this->speedFactor)
        this->xMove = this->speedFactor;
    if (this->xMove < -this->speedFactor)
        this->xMove = -this->speedFactor;
    // Y Speed cap
    if (this->yMove > this->speedFactor)
        this->yMove = this->speedFactor;
    if (this->yMove < -this->speedFactor)
        this->yMove = -this->speedFactor;
    // Z Speed cap
    if (this->zMove > this->speedFactor)
        this->zMove = this->speedFactor;
    if (this->zMove < -this->speedFactor)
        this->zMove = -this->speedFactor;

    //std::cout << "position " << this->position->toString() << " movement: ("<<this->xMove<<","<<this->yMove<<","<<this->zMove<<")" << std::endl;
}

void baseElement::beforeDraw() {
    this->position->setX(this->position->getX()+this->xMove);
    this->position->setY(this->position->getY()+this->yMove);
    this->position->setZ(this->position->getZ()+this->zMove);
    glColor3ub(this->color->getR(), this->color->getG(), this->color->getB());
    glTranslatef(this->position->getX(),this->position->getY(),this->position->getZ());
}

void baseElement::afterDraw() {
    glTranslatef(-this->position->getX(),-this->position->getY(),-this->position->getZ());
}
