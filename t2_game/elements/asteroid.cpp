#include <list>
#include <iostream>
#include <random>
#include <GLee.h>
#include <GL/freeglut.h>
#include "modelObj.hpp"
#include "baseElement.hpp"
#include "asteroid.hpp"

void asteroid::draw(){
    this->beforeDraw();

    if(this->scaleFactor != 1){
        glScalef(this->scaleFactor,this->scaleFactor,this->scaleFactor);
		// glutSolidSphere(20,100,100);
        // glutSolidCube(20);
        this->oModel->draw();
        GLfloat scaleRevert = 1/this->scaleFactor;
        glScalef(scaleRevert,scaleRevert,scaleRevert);
    }else{
        // glutSolidSphere(20,100,100);
        // glutSolidCube(20);
        this->oModel->draw();
    }

    this->afterDraw();
}
void asteroid::takeHit(GLfloat damage){
    //std::cout << "taking hit of " << damage << " against " << this->hitPoints << std::endl;
    if(damage > this->hitPoints){
        this->hitPoints = 0;
    }else{
        this->hitPoints-=damage;
        if(this->hitPoints == 0){
            if(this->mass > 100){
                bool startInCenter = true;
                GLfloat childCount = 5;
                GLfloat childMass = this->mass / childCount;
                GLfloat radius = 0;
                if(!startInCenter)
                    radius = this->getRadius()*2;
                GLfloat cSpeed = this->speedFactor*1.05f;
                if(cSpeed == 0)
                    cSpeed = 0.05f;
                std::default_random_engine generator;

                std::uniform_real_distribution<GLfloat> distX(this->position->getX() - radius,this->position->getX() + radius);
                std::uniform_real_distribution<GLfloat> distY(this->position->getY() - radius,this->position->getY() + radius);
                std::uniform_real_distribution<GLfloat> distZ(this->position->getZ() - radius,this->position->getZ() + radius);
                //to generate a random rotation, otherwise it will only mode "forward"
                std::uniform_real_distribution<GLfloat> distRot(0,360);

                //std::cout << "creating "<< childCount << " children, from parent at " << this->position->toString() << std::endl;
                for (int c = 0; c < childCount; c++) {
                    GLfloat cx = distX(generator);
                    GLfloat cy = distY(generator);
                    GLfloat cz = distZ(generator);
                    point3D* childPos = new point3D(cx,cy,cz,distRot(generator),distRot(generator),distRot(generator));
                    //std::cout << "child["<<c<<"] at " << childPos->toString() << std::endl;
                    asteroid* child = new asteroid(this->oModel,childPos,childMass,cSpeed);
                    this->children.push_back(child);
                }
            }
        }
    }
}
