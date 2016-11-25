#include <iostream>

#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <GL/freeglut.h>  // Include FreeGLUT so we can easily draw spheres and calculate our viewing frustrum
#include <SOIL.h>
#include <math.h>         // Used only for sin() and cos() functions
#include <list>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "util/globals.hpp"
#include "util/glhelp.hpp"
#include "util/camera.hpp"
#include "util/options.hpp"
#include "util/level.hpp"
#include "util/smmath.hpp"
#include "util/handlers.hpp"
#include "util/helpers/guides.hpp"
#include "elements/point3D.hpp"
#include "elements/colorRgb.hpp"
#include "elements/shoot.hpp"
#include "elements/modelObj.hpp"
#include "elements/asteroid.hpp"

using namespace std;

level* currentLvl;
void initGame()
{
    globals::gameOptions.load();

    colorRgb* astColor = new colorRgb(160,100,20);
    globals::modelObjs["asteroid1"] = new modelObj(astColor,true);
    globals::modelObjs["asteroid1"]->loadFromFile("data/models/asteroid1.obj");
    //modelObjs["asteroid1"]->drawVolume = true;
    globals::modelObjs["shoot1"] = new modelObj(new colorRgb(255,60,0),true);
    globals::modelObjs["shoot1"]->loadFromFile("data/models/shoot1.obj");
    //modelObjs["shoot1"]->drawVolume = true;

    globals::cameraFPS = new camera();
    globals::cameraFPS->setMouseSensitivity(globals::gameOptions.getMouseSensitivity());
    globals::cameraFPS->setSpeed(globals::gameOptions.getCameraSpeed());
    setFullScreen(globals::gameOptions.isFullscreen());
    // ----- GLFW Settings -----
    //glfwSetInputMode(gameWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED); // Hide the mouse cursor
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    glfwSetCursor(globals::gameWindow, cursor);
    // ----- Window and Projection Settings -----
    // Setup our viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei)globals::windowWidth, (GLsizei)globals::windowHeight);
    globals::cameraFPS->setPerspective(globals::windowHeight,globals::windowWidth);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ----- OpenGL settings -----
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set out clear colour to black, full alpha
    glfwSwapInterval(1);        // Lock to vertical sync of monitor (normally 60Hz, so 60fps)
    glEnable(GL_DEPTH_TEST);    // Enable depth testing
    glClearDepth(1.0f);         // Clear the entire depth of the depth buffer
    glDepthFunc(GL_LEQUAL);		// Set our depth function to overwrite if new value less than or equal to current value
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Ask for nicest perspective correction
    glEnable(GL_CULL_FACE); // Do not draw polygons facing away from us
    glLineWidth(2.0f);			// Set a 'chunky' line width

    //glDisable(GL_LIGHTING);
	// Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
    if(globals::gameOptions.useAmbientLight()){
        globals::ambientLight[0] = 1.0f;
        globals::ambientLight[1] = 1.0f;
        globals::ambientLight[2] = 1.0f;
        globals::ambientLight[3] = 1.0f;

        globals::diffuseLight[0] = 0;
        globals::diffuseLight[1] = 0;
        globals::diffuseLight[2] = 0;
        globals::diffuseLight[3] = 1.0f;
    }
    else{
        globals::ambientLight[0] = 0.2f;
        globals::ambientLight[1] = 0.2f;
        globals::ambientLight[2] = 0.2f;
        globals::ambientLight[3] = 1.0f;

        globals::diffuseLight[0] = 0.7f;
        globals::diffuseLight[1] = 0.7f;
        globals::diffuseLight[2] = 0.7f;
        globals::diffuseLight[3] = 1.0f;
    }

    globals::specularLight[0] = 1.0f;
    globals::specularLight[1] = 1.0f;
    globals::specularLight[2] = 1.0f;
    globals::specularLight[3] = 1.0f;

    setLights();
    // Enable colour tracking of materials
    glEnable(GL_COLOR_MATERIAL);
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    currentLvl = new level();
    // Check for any OpenGL errors (providing the location we called the function from)
    checkGLError("initGame");
}

void computeLevel() {
    if(!currentLvl->isLoaded())
        currentLvl->loadFromFile("data/levels/level01.lvl");
}

// Function to draw our spheres and position the light source
void drawScene(){
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    globals::cameraFPS->draw();
	point3D* p = globals::cameraFPS->getCurrentPosition();
    globals::lightPos[0]=p->getX();
    globals::lightPos[1]=p->getY();
    globals::lightPos[2]=p->getZ();
    setLights();
    #ifdef LDEBUG
    glTranslatef(lightPos[0],lightPos[1],lightPos[2]);
    glDisable(GL_LIGHTING);
    glColor3ub(255,255,255);
    glutWireSphere(1,10,10);
    glEnable(GL_LIGHTING);
    glTranslatef(-lightPos[0],-lightPos[1],-lightPos[2]);
    #endif
    #ifdef D_GUIDES
    //*
    //drawCheesGrid(600,20,-10);
    // Draw the lower ground-grid
    drawGround();
    // Draw the upper ground-grid, keeping a copy of our current matrix on the stack before we translate it
    glPushMatrix();
    glTranslatef(0.0f, 200.0f, 0.0f);
    drawGround();
    glPopMatrix();
    #endif

    draw3DAxis(300);

    list<shoot*>::iterator is;
    list<asteroid*>::iterator ia;
    for (is = globals::shoots.begin(); is != globals::shoots.end(); ++is) {
        if((*is)->isAlive()){
            (*is)->draw();
            for (ia = globals::asteroids.begin(); ia != globals::asteroids.end(); ++ia) {
                if((*ia)->isAlive())
                    (*is)->hitAsteroid((*ia));
            }
        }
        else
            is = globals::shoots.erase(is);
    }

    for (ia = globals::asteroids.begin(); ia != globals::asteroids.end(); ++ia) {
        if((*ia)->isAlive())
            (*ia)->draw();
        else{
            list<asteroid*> children = (*ia)->getChildren();
            list<asteroid*>::iterator ic;
            for (ic = children.begin(); ic != children.end(); ++ic) {
                globals::asteroids.push_back((*ic));
            }
            ia = globals::asteroids.erase(ia);
        }
    }

    // ----- Stop Drawing Stuff! ------
    glfwSwapBuffers(globals::gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

void drawPaused() {
    projection2D(0.45f);
    globals::textHandler->drawText("PAUSED", T2D_CENTER);//new point3D(-0.18f,-0.05f,0));
    glfwSwapBuffers(globals::gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

void drawMain() {
    projection2D(0.45f);
    globals::textHandler->drawText("Press SPACE to start", T2D_CENTER);
    glfwSwapBuffers(globals::gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

// Fire it up...
int main(int argc, char **argv)
{
    globals::textHandler = text::getMonospace();
    globals::windowWidth  = 1024;                    // Width of our window
    globals::windowHeight = 768;                    // Heightof our window
    globals::midWindowX = globals::windowWidth  / 2;         // Middle of the window horizontally
    globals::midWindowY = globals::windowHeight / 2;         // Middle of the window vertically
    globals::fullScreenMode = false;
    // Set the light source location
    globals::lightPos[0] = 2.0f;
    globals::lightPos[1] = 2.0f;
    globals::lightPos[2] = 10.0f;
    globals::lightPos[3] = 1.0f;
    // ----- Intialiase FreeGLUT -----
    // Note: We're only using freeGLUT to draw some spheres, so if you modify the code to not include any calls
    // to glutSolidSphere, then you don't need this, the header or the lib...
    glutInit(&argc, argv);
    // Initialise GLFW
    glfwInit();
    // Ask for 4x AntiAliasing (this doesn't mean we'll get it - it'll work only if the GLX_ARB_multisample extension is available)
    // Note: Hints must be provided BEFORE the window is opened! But we can't query for it with GLEE until the window is opened! Catch 22!
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create a window
    char windowTitle[] = "Space Mission 3: Lost in Space";
    globals::gameWindow = glfwCreateWindow(globals::windowWidth,globals::windowHeight,windowTitle, NULL, NULL);
    if(globals::gameWindow == NULL)
    {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(globals::gameWindow);
    setFullScreen(globals::fullScreenMode);// Will set viewport and camera perspective
    globals::setFullScreen = setFullScreen;
    // ----- Initialise GLEE -----
    // Initialise GLee once we've got a rendering context
    // Note: We don't really have to do this because it's called automatically, but if we do it - we KNOW it's been called!
    GLeeInit();

    // Check for the OpenGL extension which allows us to use vsync
    if (GLEE_GLX_SGI_swap_control)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
    // Check for the OpenGL extension which allows us to use antialiasing
    if (GLEE_ARB_multitexture)
        glDisable(GL_LINE_SMOOTH);
    else
        glEnable(GL_LINE_SMOOTH);

    // Set the mouse cursor to the centre of our window
    glfwSetCursorPos(globals::gameWindow,globals::midWindowX, globals::midWindowY);
    // Call our initGame function to set up our OpenGL options
    initGame();
    // Specify the function which should execute when the mouse is moved
    glfwSetCursorPosCallback(globals::gameWindow,handleMouseMove);
    // Specify the function which should execute when a mouse button is pressed or released
    glfwSetMouseButtonCallback(globals::gameWindow, handleMouseButton);

    globals::started = false;
    globals::paused = true;
	glfwSetKeyCallback(globals::gameWindow,handleKeypressMenu);
    // glDisable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(globals::gameWindow) && !globals::started)
    {
        drawMain();
        // Check for any OpenGL errors (providing the location we called the function from)
        checkGLError("Main loop");
    }
    glEnable(GL_DEPTH_TEST);
	// Specify the function which should execute when a key is pressed or released
	glfwSetKeyCallback(globals::gameWindow,handleKeypress);

    globals::paused = false;
    while (!glfwWindowShouldClose(globals::gameWindow))
    {
        if(globals::paused){
            drawPaused();
        }else{
			computeLevel();
            // Draw our scene
            drawScene();
            // Move our camera
            globals::cameraFPS->move();
        }
        // Check for any OpenGL errors (providing the location we called the function from)
        checkGLError("Main loop");
    }
    // Clean up GLFW and exit
    glfwTerminate();
    return 0;
}
