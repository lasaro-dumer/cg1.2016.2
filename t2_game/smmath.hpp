#ifndef smmathH
#define smmathH
const float TO_RADS = 3.141592654f / 180.0f; // The value of 1 degree in radians
// Function to convert degrees to radians
float toRads(const float &theAngleInDegrees)
{
    return theAngleInDegrees * TO_RADS;
}
#endif
