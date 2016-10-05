#include <GLee.h>         // No need to link to GL/gl.h
#include <GL/freeglut.h>
#include <math.h>
#include "shoot.hpp"
#include "point3D.hpp"
#include "colorRgb.hpp"
#include "../smmath.hpp"

void shoot::draw() {
    this->beforeDraw();
    glRotatef(-this->position->getYRot(), 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    glRotatef(-this->position->getXRot(), 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glScalef(1,1,4);
    glutSolidCube(1);
    glScalef(1,1,0.25f);
    glRotatef(this->position->getXRot(), 1.0f, 0.0f, 0.0f);        // Rotate our camera on the x-axis (looking up and down)
    glRotatef(this->position->getYRot(), 0.0f, 1.0f, 0.0f);        // Rotate our camera on the  y-axis (looking left and right)
    this->afterDraw();
    this->age++;
}

bool shoot::isAlive(){
    return this->age < this->timeToLive;
}
