#ifndef baseElementH
#define baseElementH
#include <GLee.h>
#include "point3D.hpp"
#include "colorRgb.hpp"

class baseElement {
protected:
    point3D* center;
    point3D* position;
    colorRgb* color;
    GLfloat speedFactor;
    GLfloat xMove;
    GLfloat yMove;
    GLfloat zMove;
	bool circularMove;
	GLfloat majorR, minorR, curOrbitPoint;
    void calculateMovementForward();
public:
    baseElement (point3D* pos, colorRgb* clr,GLfloat spd){
        this->center = pos;
        this->position = new point3D(0,0,0);
        this->position->update(pos);
        this->color = clr;
        this->speedFactor = spd;
        this->xMove = 0.0f;
        this->yMove = 0.0f;
        this->zMove = 0.0f;
        this->circularMove = false;
    }
    baseElement(point3D* pos):baseElement(pos,new colorRgb(255,255,255),0){};
    void setSpeed(GLfloat value){
        this->speedFactor = value;
        this->calculateMovementForward();
    }
	void setCircularMovement(point3D* center, GLfloat major, GLfloat minor=-1) {
		if(minor == -1)
            minor = major;
        this->circularMove = true;
        this->majorR = major;
        this->minorR = minor;
        this->center = center;
        this->position->update(this->center);
        this->curOrbitPoint = 0.0f;
	}
    void beforeDraw();
    void afterDraw();
    point3D* getPosition(){ return this->position; }
    virtual void draw(){}
    virtual bool isAlive(){}
};

#endif
