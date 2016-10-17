#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <GLee.h>
#include <GL/glut.h>
#include "colorRgb.hpp"
#include "point3D.hpp"
#include "modelObj.hpp"
#include "../util/smmath.hpp"

bool modelObj::loadFromFile(string path){
    FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		cout << "Impossible to open the file! <"<<path<<">" << endl;
		return false;
	}
	this->vertices.clear();
	this->faces.clear();
    char lineType[128];
    int res = fscanf(file, "%s", lineType);

    while(res != EOF){
        if (strcmp( lineType, "v" ) == 0 ){
			GLfloat x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			this->vertices.push_back(new point3D(x,y,z));
		}else if (strcmp( lineType, "f" ) == 0 ){
			int p1,p2,p3;
			fscanf(file, "%d %d %d\n", &p1, &p2, &p3 );
			vector<point3D*> face;
            face.push_back(this->vertices[p1-1]);
            face.push_back(this->vertices[p2-1]);
            face.push_back(this->vertices[p3-1]);
            this->faces.push_back(face);
		}
        res = fscanf(file, "%s", lineType);
    }
	this->center = centroid(this->vertices);
	this->radius = meanRadius(center,this->vertices);
	this->loaded = true;
}
void modelObj::draw(){
	glColor3ub(this->faceColor->getR(),this->faceColor->getG(),this->faceColor->getB());
	for (int i = 0; i < this->faces.size(); i++) {
        glBegin(GL_TRIANGLES);
	        this->faces[i][0]->draw();
	        this->faces[i][1]->draw();
	        this->faces[i][2]->draw();
        glEnd();

		if(this->drawLines){
	        glColor3ub(0,0,0);
	        glBegin(GL_LINES);
		        this->faces[i][0]->draw();
		        this->faces[i][1]->draw();

		        this->faces[i][1]->draw();
		        this->faces[i][2]->draw();

				this->faces[i][2]->draw();
		        this->faces[i][0]->draw();
	        glEnd();
			glColor3ub(this->faceColor->getR(),this->faceColor->getG(),this->faceColor->getB());
		}
    }
	if(this->drawVolume){
        glColor3ub(255,255,255);
	    glutWireSphere(this->radius, 100, 100);
	}
}
