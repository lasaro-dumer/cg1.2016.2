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
	static bool paused;
};
#endif
