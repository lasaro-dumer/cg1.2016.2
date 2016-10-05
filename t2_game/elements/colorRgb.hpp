#ifndef colorRgbH
#define colorRgbH
#include <GLee.h>

class colorRgb {
private:
    GLfloat r;
    GLfloat g;
    GLfloat b;
public:
    colorRgb (GLfloat rValue,GLfloat gValue,GLfloat bValue){
        this->r = rValue;
        this->g = gValue;
        this->b = bValue;
    }
    void setR(GLfloat value){ this->r = value;}
    void setG(GLfloat value){ this->g = value;}
    void setB(GLfloat value){ this->b = value;}
    GLfloat getR(){ return this->r;}
    GLfloat getG(){ return this->g;}
    GLfloat getB(){ return this->b;}
};
#endif
