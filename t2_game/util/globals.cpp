#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <map>
#include <list>
#include "../elements/shoot.hpp"
#include "text.hpp"
#include "options.hpp"
#include "globals.hpp"

text* globals::textHandler;
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
bool globals::started;
bool globals::paused;
GLint globals::windowPosX   = 50;
GLint globals::windowPosY   = 50;
GLFWwindow* globals::gameWindow;
GLfloat globals::ambientLight[4];
GLfloat globals::diffuseLight[4];
GLfloat globals::specularLight[4];
options globals::gameOptions;
