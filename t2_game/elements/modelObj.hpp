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
    bool loaded;
public:
    vector<point3D*> vertices;
    point3D* center;
    GLfloat radius;
    bool drawVolume=false;
    modelObj(colorRgb* fColor, bool dLines){
        this->faceColor = fColor;
        this->drawLines = dLines;
        this->loaded = false;
    }
    colorRgb* getColor(){ return this->faceColor;};
    bool loadFromFile(string path);
    void draw();
    bool isLoaded(){ return this->loaded; }
};

#endif
