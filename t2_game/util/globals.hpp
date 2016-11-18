#ifndef globalsH
#define globalsH
#include <map>
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include "text.hpp"
#include "camera.hpp"
#include "options.hpp"
#include "../elements/modelObj.hpp"
#include "../elements/shoot.hpp"
#include "../elements/asteroid.hpp"

typedef void (* setFullScreenfun)(bool);

class globals {
private:
public:
	static text* textHandler;
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
	static bool started;
	static bool paused;
	static GLint windowPosX;      // Windowed mode's top-left corner x
	static GLint windowPosY;      // Windowed mode's top-left corner y
	static GLFWwindow* gameWindow;
	// Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
	static GLfloat ambientLight[];
	static GLfloat diffuseLight[];
	static GLfloat specularLight[];
	static options gameOptions;
};
#endif
