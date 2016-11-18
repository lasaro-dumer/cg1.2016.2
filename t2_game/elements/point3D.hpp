#ifndef point3DH
#define point3DH
#include <GLee.h>
#include <string>
#include <sstream>

using namespace std;

class point3D {
private:
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat xr;
    GLfloat yr;
    GLfloat zr;
public:
    point3D (GLfloat xpos,GLfloat ypos,GLfloat zpos){
        this->x=xpos;
        this->y=ypos;
        this->z=zpos;
        this->xr=0;
        this->yr=0;
        this->zr=0;
    }
    point3D (GLfloat xpos,GLfloat ypos,GLfloat zpos,GLfloat xrot,GLfloat yrot,GLfloat zrot){
        this->x=xpos;
        this->y=ypos;
        this->z=zpos;
        this->xr=xrot;
        this->yr=yrot;
        this->zr=zrot;
    }
    void setX(GLfloat value){ this->x = value;}
    void setY(GLfloat value){ this->y = value;}
    void setZ(GLfloat value){ this->z = value;}
    void setXRot(GLfloat value){ this->xr = value;}
    void setYRot(GLfloat value){ this->yr = value;}
    void setZRot(GLfloat value){ this->zr = value;}
    GLfloat getX(){ return this->x;}
    GLfloat getY(){ return this->y;}
    GLfloat getZ(){ return this->z;}
    GLfloat getXRot(){ return this->xr;}
    GLfloat getYRot(){ return this->yr;}
    GLfloat getZRot(){ return this->zr;}
    void draw(){
        glVertex3f(this->x,this->y,this->z);
    }
	void update(point3D* newPos) {
		this->setX(newPos->getX());
		this->setY(newPos->getY());
		this->setZ(newPos->getZ());
		this->setXRot(newPos->getXRot());
		this->setYRot(newPos->getYRot());
		this->setZRot(newPos->getZRot());
	}
    string toString(){
        stringstream ss;
        ss << "("<<this->x<<","<<this->y<<","<<this->z<<")@("<<this->xr<<","<<this->yr<<","<<this->zr<<")";
        return ss.str();
    }
};
#endif
