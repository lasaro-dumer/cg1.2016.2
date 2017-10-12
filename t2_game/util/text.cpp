#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <GLee.h>
#include "../elements/point3D.hpp"
#include "text.hpp"

using namespace std;

GLuint text::loadFont(string name) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	//...
	// Load and generate the texture
	int width, height;
    stringstream ss;
    ss << "data/fonts/" << name << ".jpg";
    string fontFile = ss.str();
	unsigned char* image = SOIL_load_image(fontFile.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	std::cout << "Loaded font "<<name << " in texture "<< texture << std::endl;
	return texture;
}

letterValues* text::setLetterValues(char *ch){
	if(chars.find(*ch) != chars.end())
		return chars[*ch];
	GLfloat col=this->repCol;
	GLfloat lin=this->repLine;
	bool found = false;
	// char ch = ' ';
	for (GLfloat l = 0; l < this->lines.size(); l++) {
	    for (GLfloat c = 0; c < this->lines[l].size(); c++) {
	        if(this->lines[l][c] == (*ch)){
	            col=c;
	            lin=l;
	            found=true;
	            break;
	        }
	    }
	    if(found)
	        break;
	}

	letterValues* lv = new letterValues();
	lv->width	=this->letterWidth;
	lv->height	=this->letterHeight;
	lv->left	=lv->width	* (col) 	+ this->pixelWidth;
	lv->right	=lv->left	+ lv->width - this->pixelWidth;
	lv->top		=lv->height	* (lin)		+ this->pixelHeight;
	lv->bottom	=lv->top	+ lv->height- this->pixelHeight;
	chars[*ch] = lv;
	#ifdef DEBUG
	std::cout << "setted " << (*ch);
	std::cout << " from (" << lv->left  << "," << lv->top;
	std::cout << ") to ("  << lv->right << "," << lv->bottom << ")";
	std::cout << " with "  << lv->width << "x" << lv->height << std::endl;
	#endif
	return chars[*ch];
}

void text::drawText(string aText, GLint align) {
	GLfloat x = 0;
	GLfloat y = this->letterHeight/-2;
	GLfloat z = 0;
	if(align == T2D_LEFT){
		x = (aText.size() * this->letterWidth)*-1;
	}else if(align == T2D_RIGHT){
		x = 0;
	}else{//T2D_CENTER
		x = ((aText.size() / 2) * this->letterWidth)*-1;
	}
	this->drawText(aText, new point3D(x,y,z));
}

void text::drawText(string aText,point3D* pos) {
	glDisable(GL_DEPTH_TEST);
	if(this->textureId==-1){
		this->textureId = this->loadFont(this->fontName);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, this->textureId);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(pos != nullptr)
		glTranslatef(pos->getX(), pos->getY(), pos->getZ());

	glBegin(GL_QUADS);
	GLfloat lX = 0;
	for (GLint c = 0; c < aText.size(); c++) {
		letterValues* lv = this->setLetterValues(&aText[c]);
		glTexCoord2f(lv->left , lv->bottom);glVertex2f(lX			, 0);
		glTexCoord2f(lv->right, lv->bottom);glVertex2f(lX+lv->width	, 0);
		glTexCoord2f(lv->right, lv->top);	glVertex2f(lX+lv->width	, lv->height);
		glTexCoord2f(lv->left , lv->top);	glVertex2f(lX			, lv->height);
		lX+=lv->width;
	}
	glEnd();

	if(pos != nullptr)
		glTranslatef(-pos->getX(), -pos->getY(), -pos->getZ());
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_DEPTH_TEST);
}
