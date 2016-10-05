#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "colorRgb.hpp"
#include "point3D.hpp"
#include "modelObj.hpp"

bool modelObj::loadFromFile(string path){
	vector<point3D*> lPts;
    FILE * file = fopen(path.c_str(), "r");
	if( file == NULL ){
		cout << "Impossible to open the file! <"<<path<<">" << endl;
		getchar();
		return false;
	}
    char lineType[128];
    int res = fscanf(file, "%s", lineType);
	
    while(res != EOF){
        if (strcmp( lineType, "v" ) == 0 ){
			GLfloat x,y,z;
			fscanf(file, "%f %f %f\n", &x, &y, &z );
			lPts.push_back(new point3D(x,y,z));
		}else if (strcmp( lineType, "f" ) == 0 ){
			int p1,p2,p3;
			fscanf(file, "%d %d %d\n", &p1, &p2, &p3 );
			vector<point3D*> face;
            face.push_back(lPts[p1-1]);
            face.push_back(lPts[p2-1]);
            face.push_back(lPts[p3-1]);
            this->faces.push_back(face);
		}
        res = fscanf(file, "%s", lineType);
    }
    /*
    for (int i = 0; i < lPts.size(); i++) {
        point3D* p = lPts[i];
        std::cout << "lPts["<<i<<"]= ("<<p->getX() <<","<<p->getY() <<","<<p->getZ()<<")" << std::endl;
    }
    //*/
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

}
