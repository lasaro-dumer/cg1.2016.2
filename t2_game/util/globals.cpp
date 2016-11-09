#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <map>
#include <list>
#include "../elements/shoot.hpp"
#include "globals.hpp"

camera* globals::cameraFPS;
GLint globals::windowWidth;
GLint globals::windowHeight;
GLfloat globals::midWindowX;
GLfloat globals::midWindowY;
map<string,modelObj*> globals::modelObjs;
list<shoot*> globals::shoots;
list<asteroid*> globals::asteroids;
GLfloat globals::lightPos[4];
bool globals::fullScreenMode;
setFullScreenfun globals::setFullScreen;
