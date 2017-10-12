#ifndef textH
#define textH
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <GLee.h>
#include <SOIL/SOIL.h>
#include "../elements/point3D.hpp"

using namespace std;
struct letterValues{
	GLfloat width;
	GLfloat height;
	GLfloat top;
	GLfloat bottom;
	GLfloat left;
	GLfloat right;
};

const GLint T2D_LEFT = -1;
const GLint T2D_CENTER = 0;
const GLint T2D_RIGHT = 1;

class text{
private:
	std::vector<string> lines={
		"ABCDEFGHIJKLMNOP",
		"QRSTUVWXYZabcdef",
		"ghijklmnopqrstuv",
		"wxyzáàãâéèẽêíìĩî",
		"óòõôúùũûç|[]{}",
		"0123456789,.?!@#",
		"$%&*()-+=;\"' ",	//ignore the % syntax warning   //we have a space mapping at the end
		":\\/<>_¹²³ªº",
	};
	string fontName;
	std::map<char, letterValues*> chars;
	GLint textureId;
	GLint fontWidth;
	GLint fontHeight;
	GLint imageWidth;
	GLint imageHeight;
	GLfloat pixelWidth;
	GLfloat pixelHeight;
	GLfloat letterWidth;
	GLfloat letterHeight;
	GLint repCol;
	GLint repLine;
	GLuint loadFont(string name);
	letterValues* setLetterValues(char *ch);
public:
	text(string fN, GLint w, GLint h, GLint fW, GLint fH, GLint rC, GLint rL){
		this->fontName = fN;
		this->fontWidth = fW;
		this->fontHeight= fH;
		this->imageWidth = w;
		this->imageHeight= h;
		this->pixelWidth = (1.0f/this->imageWidth);
		this->pixelHeight = (1.0f/this->imageHeight);
	    this->letterWidth	= this->pixelWidth	* this->fontWidth;
	    this->letterHeight	= this->pixelHeight	* this->fontHeight;
		this->repCol = rC;
		this->repLine= rL;
		this->textureId = -1;
	}
	static text* getMonospace(){
		text* _monospace = new text("monospace", 512, 512, 30, 59, 12, 7);
		return _monospace;
	}
	void drawText(string aText, point3D* pos = nullptr);
	void drawText(string aText, GLint align);
};
#endif
