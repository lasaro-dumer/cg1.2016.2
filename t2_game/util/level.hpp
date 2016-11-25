#ifndef levelH
#define levelH
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <map>
#include "../elements/asteroid.hpp"
#include "globals.hpp"

class level {
private:
    bool loaded;
public:
    level(){
        this->loaded = false;
	}
    bool isLoaded(){ return this->loaded; }
    bool loadFromFile(string path){
        FILE * file = fopen(path.c_str(), "r");
    	if( file == NULL ){
    		cout << "Impossible to open the file! <"<<path<<">" << endl;
            this->loaded = false;
    		return false;
    	}

        char lineType[128];
        int res = fscanf(file, "%s", lineType);
        /*
        base asteroid1 1000.0 0.5
        pos 0 0 0
        orbit 100 150
        sub_start
        base asteroid1 500.0 0.5
        orbit 50 70
        sub_endd
        */
        list<asteroid*> v;
        GLfloat mass, speed;
        GLfloat x, y, z, major, minor;
        char model[1024];
        asteroid* ast;
        point3D* pos;
        bool isNew = false, isSub = false, hasOrbit = false;
        while(res != EOF){
            std::cout << "lineType: " << lineType << std::endl;
            if (strcmp( lineType, "base" ) == 0 ){
                fscanf(file, "%s %f %f\n", model, &mass, &speed);
                isNew = true;
                hasOrbit = false;
                major = 0;
                minor = 0;
            }else if (strcmp( lineType, "pos" ) == 0 && !isSub){
                fscanf(file, "%f %f %f\n", &x, &y, &z );
                pos = new point3D(x,y,z);
            }else if (strcmp( lineType, "orbit" ) == 0 ){
                hasOrbit = true;
                fscanf(file, "%f %f\n", &major, &minor);
            }else if (strcmp( lineType, "sub_start" ) == 0 ){
                isSub = true;
            }else if (strcmp( lineType, "sub_end" ) == 0 ){
                isSub = false;
            }
            res = fscanf(file, "%s", lineType);
            if(res == EOF || (strcmp( lineType, "base" ) == 0 )){
                if(isNew){
                    std::cout << "Adding a " <<model <<" with " <<mass<<" and "<<speed<<" at "<< pos->toString() << std::endl;
                    asteroid* ast;
                    if(hasOrbit)
                        ast = new asteroid(globals::modelObjs[model], pos, mass, speed, major, minor);
                    else
                        ast = new asteroid(globals::modelObjs[model], pos, mass, 0);//let's ignore speed if not orbiting; will get a stationary object
                    pos = ast->getPosition();
                    v.push_back(ast);
                    isNew = false;
                }
            }
        }

        globals::asteroids = v;

        this->loaded = true;
        std::cout << "Loaded level " << path << std::endl;
        return true;
    }

};

#endif
