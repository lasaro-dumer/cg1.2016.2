#ifndef asteroidH
#define asteroidH
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
public:
    asteroid (modelObj* mObj, point3D* pos, GLfloat m):baseElement(pos,mObj->getColor(),defaultSpeed){
        this->oModel = mObj;
        this->mass = m;
        this->scaleFactor = (this->mass/baseMass);
        this->calculateMovementForward();
    }
    void draw(){
        this->beforeDraw();

        if(this->scaleFactor != 1){
            glScalef(this->scaleFactor,this->scaleFactor,this->scaleFactor);
            this->oModel->draw();
            GLfloat scaleRevert = 1/this->scaleFactor;
            glScalef(scaleRevert,scaleRevert,scaleRevert);
        }else{
            this->oModel->draw();
        }

        this->afterDraw();
    }
};

#endif
