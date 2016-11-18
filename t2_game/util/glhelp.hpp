#include <iostream>
#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <GL/freeglut.h>
#include "globals.hpp"

using namespace std;

// Function to check if OpenGL is having issues - pass it a unique string of some kind to track down where in the code it's moaning
void checkGLError(const char * errorLocation)
{
    unsigned int gle = glGetError();
    if (gle != GL_NO_ERROR)
    {
        cout << "GL Error discovered from caller " << errorLocation << ": ";
        switch (gle)
        {
            case GL_INVALID_ENUM:       cout << "Invalid enum."; break;
            case GL_INVALID_VALUE:      cout << "Invalid value."; break;
            case GL_INVALID_OPERATION:  cout << "Invalid Operation."; break;
            case GL_STACK_OVERFLOW:     cout << "Stack overflow."; break;
            case GL_STACK_UNDERFLOW:    cout << "Stack underflow."; break;
            case GL_OUT_OF_MEMORY:      cout << "Out of memory."; break;
            default:                    cout << "Unknown error! Enum code is: " << gle; break;
        }
        cout << endl;
    }
}

void setFullScreen(bool toFullScreen) {
    if(globals::fullScreenMode == toFullScreen)
        return;
    globals::fullScreenMode = toFullScreen;

    glfwGetWindowPos(globals::gameWindow, &globals::windowPosX, &globals::windowPosY);
    GLFWmonitor* monitor = NULL;
    if (globals::fullScreenMode) {                     // Full-screen mode
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(globals::gameOptions.isFullscreenMaxSize()){
            globals::windowWidth = mode->width;
            globals::windowHeight = mode->height;
        }else{
            globals::windowWidth = globals::gameOptions.getFullscreenWidth();
            globals::windowHeight = globals::gameOptions.getFullscreenHeight();
        }
    } else {                                         // Windowed mode
        globals::windowWidth = globals::gameOptions.getWindowedWidth();
        globals::windowHeight = globals::gameOptions.getWindowedHeight();
    }
    globals::midWindowX = globals::windowWidth  / 2;
    globals::midWindowY = globals::windowHeight / 2;
    std::cout << "setting windowWidth: " << globals::windowWidth << " & windowHeight: " << globals::windowHeight << std::endl;
    glfwSetWindowMonitor(globals::gameWindow,monitor,globals::windowPosX,globals::windowPosY,globals::windowWidth,globals::windowHeight,GLFW_DONT_CARE);
    glfwSetWindowSize(globals::gameWindow,globals::windowWidth,globals::windowHeight);
    glViewport(0, 0, (GLsizei)globals::windowWidth, (GLsizei)globals::windowHeight);
    globals::cameraFPS->setPerspective(globals::windowHeight,globals::windowWidth);
}

void setLights() {
    // ---- Set up OpenGL lighting -----
    glShadeModel(GL_SMOOTH);    // Enable (gouraud) shading
    // Use our shiny material and magnitude
    // Define the shininess of the material we'll use to draw things
    GLfloat materialSpecularReflectance[] = { 0, 0, 0, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularReflectance);
    GLint specularMagnitude = 128; // Define how "tight" our specular highlights are (larger number = smaller specular highlight). The valid range is is 1 to 128
    glMateriali(GL_FRONT, GL_SHININESS, specularMagnitude);
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT,  globals::ambientLight);      // Specify ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  globals::diffuseLight);      // Specify diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, globals::specularLight);     // Specify specular light properties
    glLightfv(GL_LIGHT0, GL_POSITION, globals::lightPos);          // Specify the position of the light
    glEnable(GL_LIGHT0);
}

void projection2D(GLfloat zoom = 1) {
    GLfloat aspect = (GLfloat)globals::windowWidth / (GLfloat)globals::windowHeight;
    // Projection clipping area
    GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (globals::windowWidth >= globals::windowHeight) {
       clipAreaXLeft   = -zoom * aspect;
       clipAreaXRight  = zoom * aspect;
       clipAreaYBottom = -zoom;
       clipAreaYTop    = zoom;
    } else {
       clipAreaXLeft   = -zoom;
       clipAreaXRight  = zoom;
       clipAreaYBottom = -zoom / aspect;
       clipAreaYTop    = zoom / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);
}
