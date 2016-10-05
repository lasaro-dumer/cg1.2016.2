#ifndef modelObjH
#define modelObjH
#include <vector>
#include <string>
#include "colorRgb.hpp"
#include "point3D.hpp"

using namespace std;

class modelObj {
private:
    colorRgb* faceColor;
    bool drawLines;
    vector< vector<point3D*> > faces;
public:
    modelObj(colorRgb* fColor, bool dLines){
        this->faceColor = fColor;
        this->drawLines = dLines;
    }
    colorRgb* getColor(){ return this->faceColor;};
    bool loadFromFile(string path);
    void draw();
};

#endif
