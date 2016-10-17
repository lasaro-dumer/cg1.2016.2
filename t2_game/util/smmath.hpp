#ifndef smmathH
#define smmathH
#include <vector>
#include "../elements/point3D.hpp"
const float TO_RADS = 3.141592654f / 180.0f; // The value of 1 degree in radians
// Function to convert degrees to radians
float toRads(const float &theAngleInDegrees);
point3D* centroid(vector<point3D*> vertices);
GLfloat meanRadius(point3D* center, vector<point3D*> vertices);
#endif
