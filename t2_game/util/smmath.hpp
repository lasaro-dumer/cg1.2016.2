#ifndef smmathH
#define smmathH
#include <vector>
#include "../elements/point3D.hpp"
const float PI = 3.141592654f;
const float TO_RADS = PI / 180.0f; // The value of 1 degree in radians
// Function to convert degrees to radians
float toRads(const float &theAngleInDegrees);
point3D* centroid(vector<point3D*> vertices);
GLfloat meanRadius(point3D* center, vector<point3D*> vertices);
point3D* positionInCircle(point3D* center, GLfloat orbitPoint, GLfloat major, GLfloat minor);
#endif
