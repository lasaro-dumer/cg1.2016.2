#include <GLee.h>         // No need to link to GL/gl.h
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include "shoot.hpp"
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "../util/smmath.hpp"

void shoot::draw() {
    this->beforeDraw();
    glRotatef(-this->position->getYRot(), 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    glRotatef(-this->position->getXRot(), 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    if(this->oModel->isLoaded()){
        this->oModel->draw();
    }else{
        glScalef(1,1,4);
        glutSolidCube(1);
        glScalef(1,1,0.25f);
    }
    glRotatef(this->position->getXRot(), 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glRotatef(this->position->getYRot(), 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    this->afterDraw();
    this->age++;
	// std::cout << "shoot at " << this->position->toString() << std::endl;
}

bool shoot::hitAsteroid(asteroid* a){
    point3D* ac = a->getPosition();//getModel()->center;
    point3D* c = this->position;//oModel->center;
    GLfloat xd = pow(c->getX() - ac->getX(),2);
    GLfloat yd = pow(c->getY() - ac->getY(),2);
    GLfloat zd = pow(c->getZ() - ac->getZ(),2);
    //d = sq (xb-xa)^2 + (yb-ya)^2
    GLfloat d = sqrt(xd+yd+zd);
    GLfloat hitD = this->oModel->radius + a->getRadius();
    //std::cout << "d: " << d << " hitD: " << hitD << std::endl;
    if(d < hitD){
        a->takeHit(this->damage);
        this->age = this->timeToLive;
        return true;
    }
    return false;
}

bool shoot::isAlive(){
    return this->age < this->timeToLive;
}
