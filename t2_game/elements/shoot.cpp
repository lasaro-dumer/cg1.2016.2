#include <GLee.h>         // No need to link to GL/gl.h
#include <GL/freeglut.h>
#include <math.h>
#include "shoot.hpp"
#include "point3D.hpp"
#include "../smmath.hpp"

void shoot::calculateMovement(){
    // Control X-Axis movement
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
}

void shoot::draw() {
    this->position->setX(this->position->getX()+this->xMove);
    this->position->setY(this->position->getY()+this->yMove);
    this->position->setZ(this->position->getZ()+this->zMove);
    glTranslatef(this->position->getX(),this->position->getY(),this->position->getZ());
    glutSolidCube(1);
    glTranslatef(-this->position->getX(),-this->position->getY(),-this->position->getZ());
    this->age++;
}

bool shoot::isAlive(){
    return this->age < this->timeToLive;
}
