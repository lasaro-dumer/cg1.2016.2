#ifndef asteroidH
#define asteroidH
#include <list>
#include "modelObj.hpp"
#include "baseElement.hpp"

class asteroid : public baseElement {
private:
    modelObj* oModel;
    GLfloat mass;
    //mass = baseMass => scale = 1
    constexpr static GLfloat baseMass = 1000;
    constexpr static GLfloat defaultSpeed = 1;
    GLfloat scaleFactor;
    GLfloat hitPoints;
    list<asteroid*> children;
public:
    asteroid (modelObj* mObj, point3D* pos, GLfloat m,GLfloat s):baseElement(pos,mObj->getColor(),s){
        this->oModel = mObj;
        this->mass = m;
        this->scaleFactor = (this->mass/baseMass);
        this->calculateMovementForward();
        this->hitPoints = 10;
    }
    asteroid (modelObj* mObj, point3D* pos, GLfloat m):asteroid(mObj,pos,m,defaultSpeed){
    }
    void draw();
    void takeHit(GLfloat damage);
    modelObj* getModel(){ return this->oModel; }
    GLfloat getRadius(){ return this->oModel->radius * this->scaleFactor; }
    bool isAlive(){ return this->hitPoints > 0; }
    list<asteroid*> getChildren(){ return this->children; }
};

#endif
