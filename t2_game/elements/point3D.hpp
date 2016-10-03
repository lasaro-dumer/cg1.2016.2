#ifndef point3DH
#define point3DH
#include <GLee.h>

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
};
#endif
