#include <GLee.h>
#include <math.h>
#include <iostream>
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "baseElement.hpp"
#include "../util/smmath.hpp"

void baseElement::calculateMovementForward(){
    this->xMove = 0.0f;
    this->yMove = 0.0f;
    this->zMove = 0.0f;
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

void baseElement::beforeDraw() {
	if(this->circularMove){
        this->position->update(positionInCircle(this->center, this->curOrbitPoint, this->majorR, this->minorR));
	}else{
		this->position->increment(this->xMove, this->yMove, this->zMove);
    }
    glColor3ub(this->color->getR(), this->color->getG(), this->color->getB());
    glTranslatef(this->position->getX(),this->position->getY(),this->position->getZ());
}

void baseElement::afterDraw() {
    glTranslatef(-this->position->getX(),-this->position->getY(),-this->position->getZ());
    if (this->circularMove) {
        this->curOrbitPoint+=(this->speedFactor/100);
        if (this->curOrbitPoint >= 1)
            this->curOrbitPoint = 0;
        #ifdef DEBUG
        glColor3ub(0,255,0);
        // std::cout << "center: "<< this->center->toString() << " pos: " << this->position->toString() << std::endl;
		glBegin(GL_LINES);
            glVertex3f(this->center->getX(),this->center->getY(),this->center->getZ());
            // glVertex3f(0,0,0);
            glVertex3f(this->position->getX(),this->position->getY(),this->position->getZ());
        glEnd();
        glBegin(GL_LINE_STRIP);
            for (GLfloat p = 0; p <= 1; p+=(this->speedFactor/100)) {
                point3D* v = positionInCircle(this->center, p, this->majorR, this->minorR);
                glVertex3f(v->getX(),v->getY(),v->getZ());
            }
        glEnd();
        #endif
    }
}
