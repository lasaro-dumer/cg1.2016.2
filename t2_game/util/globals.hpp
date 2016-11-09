#ifndef globalsH
#define globalsH
#include <map>
#include "camera.hpp"
#include "../elements/modelObj.hpp"
#include "../elements/shoot.hpp"
#include "../elements/asteroid.hpp"

typedef void (* setFullScreenfun)(bool);

class globals {
private:
public:
	static camera* cameraFPS;
	static GLint windowWidth;
	static GLint windowHeight;
	static GLfloat midWindowX;
	static GLfloat midWindowY;
	static map<string,modelObj*> modelObjs;
	static list<shoot*> shoots;
	static list<asteroid*> asteroids;
	static GLfloat  lightPos[];
	static bool fullScreenMode;
	static setFullScreenfun setFullScreen;
	// static void setCameraFPS(camera* c) { cameraFPS = c; }
	// static void setWindowWidth(GLint ww) {
	// 	windowWidth = ww;
	// 	midWindowX = ww / 2;
	// }
	// static void setWindowHeight(GLint wh) {
	// 	windowHeight = wh;
	// 	midWindowY = wh / 2;
	// }
	// static void putModelObj(string name,modelObj* model) {
	// 	modelObjs[name] = model;
	// }
	// static camera* getCameraFPS(){ return cameraFPS; }
	// static GLint getWindowWidth(){ return windowWidth; }
	// static GLint getWindowHeight(){ return windowHeight; }
	// static GLfloat getMidWindowX(){ return midWindowX; }
	// static GLfloat getMidWindowY(){ return midWindowY; }
	// static modelObj* getModelObj(string name){ return modelObjs[name]; }
};
#endif
