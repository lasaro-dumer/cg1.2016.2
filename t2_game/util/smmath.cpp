#include <vector>
#include <math.h>
#include "smmath.hpp"
#include "../elements/point3D.hpp"
// Function to convert degrees to radians
float toRads(const float &theAngleInDegrees)
{
    return theAngleInDegrees * TO_RADS;
}
point3D* centroid(vector<point3D*> vertices){
    GLfloat xSum=0,ySum=0,zSum=0;
    GLfloat count = vertices.size() == 0.0f ? 1.0f : (GLfloat)vertices.size();
    for (int i = 0; i < vertices.size(); i++) {
        xSum+=vertices[i]->getX();
        ySum+=vertices[i]->getY();
        zSum+=vertices[i]->getZ();
    }
    GLfloat xMean = xSum/count;
    GLfloat yMean = ySum/count;
    GLfloat zMean = zSum/count;
    return new point3D(xMean,yMean,zMean);
}

GLfloat meanRadius(point3D* center, vector<point3D*> vertices){
    GLfloat dSum=0;
    GLfloat count = vertices.size() == 0.0f ? 1.0f : (GLfloat)vertices.size();
    for (int i = 0; i < vertices.size(); i++) {
        GLfloat xd = pow(center->getX() - vertices[i]->getX(),2);
        GLfloat yd = pow(center->getY() - vertices[i]->getY(),2);
        GLfloat zd = pow(center->getZ() - vertices[i]->getZ(),2);
        //d = sq (xb-xa)^2 + (yb-ya)^2
        dSum += sqrt(xd+yd+zd);
    }
    return dSum/count;
}

point3D* positionInCircle(point3D* center, GLfloat orbitPoint, GLfloat major, GLfloat minor) {
		//majorR*sin(2*pi*orbitPoint),0,minorR*cos(2*pi*orbitPoint)
        GLfloat x = major*sin(2*PI*orbitPoint);
        GLfloat y = 0;
        GLfloat z = minor*cos(2*PI*orbitPoint);
		return new point3D(center->getX()+x, center->getY()+y, center->getZ()+z);
}
