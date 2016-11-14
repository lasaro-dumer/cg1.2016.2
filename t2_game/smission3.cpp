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
#include "util/camera.hpp"
#include "util/options.hpp"
#include "util/smmath.hpp"
#include "util/handlers.hpp"
#include "util/helpers/guides.hpp"
#include "elements/point3D.hpp"
#include "elements/colorRgb.hpp"
#include "elements/shoot.hpp"
#include "elements/modelObj.hpp"
#include "elements/asteroid.hpp"

using namespace std;

GLint windowPosX   = 50;      // Windowed mode's top-left corner x
GLint windowPosY   = 50;      // Windowed mode's top-left corner y

GLFWwindow* gameWindow;
// Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
GLfloat  ambientLight[4], diffuseLight[4], specularLight[4];
char windowTitle[] = "Space Mission 3: Lost in Space";
options gameOptions;
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

    glfwGetWindowPos(gameWindow, &windowPosX, &windowPosY);
    GLFWmonitor* monitor = NULL;
    if (globals::fullScreenMode) {                     // Full-screen mode
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        if(gameOptions.isFullscreenMaxSize()){
            globals::windowWidth = mode->width;
            globals::windowHeight = mode->height;
        }else{
            globals::windowWidth = gameOptions.getFullscreenWidth();
            globals::windowHeight = gameOptions.getFullscreenHeight();
        }
    } else {                                         // Windowed mode
        globals::windowWidth = gameOptions.getWindowedWidth();
        globals::windowHeight = gameOptions.getWindowedHeight();
    }
    globals::midWindowX = globals::windowWidth  / 2;
    globals::midWindowY = globals::windowHeight / 2;
    std::cout << "setting windowWidth: " << globals::windowWidth << " & windowHeight: " << globals::windowHeight << std::endl;
    glfwSetWindowMonitor(gameWindow,monitor,windowPosX,windowPosY,globals::windowWidth,globals::windowHeight,GLFW_DONT_CARE);
    glfwSetWindowSize(gameWindow,globals::windowWidth,globals::windowHeight);
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
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);      // Specify ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);      // Specify diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);     // Specify specular light properties
    glLightfv(GL_LIGHT0, GL_POSITION, globals::lightPos);          // Specify the position of the light
    glEnable(GL_LIGHT0);
}

void initGame()
{
    gameOptions.load();

    colorRgb* astColor = new colorRgb(160,100,20);
    globals::modelObjs["asteroid1"] = new modelObj(astColor,true);
    globals::modelObjs["asteroid1"]->loadFromFile("data/models/asteroid1.obj");
    //modelObjs["asteroid1"]->drawVolume = true;
    globals::modelObjs["shoot1"] = new modelObj(new colorRgb(255,60,0),true);
    globals::modelObjs["shoot1"]->loadFromFile("data/models/shoot1.obj");
    //modelObjs["shoot1"]->drawVolume = true;

    globals::cameraFPS = new camera();
    globals::cameraFPS->setMouseSensitivity(gameOptions.getMouseSensitivity());
    globals::cameraFPS->setSpeed(gameOptions.getSpeed());
    setFullScreen(gameOptions.isFullscreen());
    // ----- GLFW Settings -----
    //glfwSetInputMode(gameWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED); // Hide the mouse cursor
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    glfwSetCursor(gameWindow, cursor);
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
    if(gameOptions.useAmbientLight()){
        ambientLight[0] = 1.0f;
        ambientLight[1] = 1.0f;
        ambientLight[2] = 1.0f;
        ambientLight[3] = 1.0f;

        diffuseLight[0] = 0;
        diffuseLight[1] = 0;
        diffuseLight[2] = 0;
        diffuseLight[3] = 1.0f;
    }
    else{
        ambientLight[0] = 0.2f;
        ambientLight[1] = 0.2f;
        ambientLight[2] = 0.2f;
        ambientLight[3] = 1.0f;

        diffuseLight[0] = 0.7f;
        diffuseLight[1] = 0.7f;
        diffuseLight[2] = 0.7f;
        diffuseLight[3] = 1.0f;
    }

    specularLight[0] = 1.0f;
    specularLight[1] = 1.0f;
    specularLight[2] = 1.0f;
    specularLight[3] = 1.0f;

    setLights();
    // Enable colour tracking of materials
    glEnable(GL_COLOR_MATERIAL);
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    globals::asteroids.push_back(new asteroid(globals::modelObjs["asteroid1"],new point3D(50,0,50)    ,1000.0f,0.0f));
    globals::asteroids.push_back(new asteroid(globals::modelObjs["asteroid1"],new point3D(0,0,0,1,1,1),101.0f ,0.05f));

    // Check for any OpenGL errors (providing the location we called the function from)
    checkGLError("initGame");
}

void drawStrokeText(char*s,int x,int y,int z)
{
    glPushMatrix();
    glTranslatef(x, y+8,z);
    glScalef(0.5f,0.5f,z);
    // GLUT_STROKE_ROMAN
    // GLUT_STROKE_MONO_ROMAN (fixed width font: 104.76 units wide).
    for (int i=0; i<strlen(s); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN , s[i]);
    }
    glPopMatrix();
}
void drawTexts() {
    const char* text1 = "Hello world";
    glColor3ub(0,200,00);
    glRasterPos2f(5, 5);
	for(int l=0; l<strlen(text1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text1[l]);
    // drawStrokeText(text1,5,5,5);
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
    drawTexts();
    //*
    //drawCheesGrid(600,20,-10);
    // Draw the lower ground-grid
    drawGround();
    // Draw the upper ground-grid, keeping a copy of our current matrix on the stack before we translate it
    glPushMatrix();
    glTranslatef(0.0f, 200.0f, 0.0f);
    drawGround();
    glPopMatrix();

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
    glfwSwapBuffers(gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

void drawPaused() {
    GLfloat aspect = (GLfloat)globals::windowWidth / (GLfloat)globals::windowHeight;
    // Projection clipping area
    GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (globals::windowWidth >= globals::windowHeight) {
       clipAreaXLeft   = -1.0 * aspect;
       clipAreaXRight  = 1.0 * aspect;
       clipAreaYBottom = -1.0;
       clipAreaYTop    = 1.0;
    } else {
       clipAreaXLeft   = -1.0;
       clipAreaXRight  = 1.0;
       clipAreaYBottom = -1.0 / aspect;
       clipAreaYTop    = 1.0 / aspect;
    }
    gluOrtho2D(clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop);

    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const char* text1 = "PAUSED";
    glColor3ub(0,200,0);
    glRasterPos2f(-0.1, 0);
	for(int l=0; l<strlen(text1); l++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text1[l]);

    draw2DAxis(2);
    // glBegin(GL_LINES);
    //     glColor3ub(200,200,0);
    //     glVertex2f(-0.1, 0.1);
    //     glVertex2f( 0.1, 0.1);
    // glEnd();

    // ----- Stop Drawing Stuff! ------
    glfwSwapBuffers(gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

void drawMain() {
    GLfloat aspect = (GLfloat)globals::windowWidth / (GLfloat)globals::windowHeight;
    // Projection clipping area
    GLdouble clipAreaXLeft, clipAreaXRight, clipAreaYBottom, clipAreaYTop;
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    GLfloat zoom = 0.45f;
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

    // glTranslatef(-0.6,0,0);
    //glDisable(GL_DEPTH_TEST);
    globals::textHandler->drawText("Press SPACE to start", new point3D(-0.58f,-0.05f,0));
    // glEnable(GL_DEPTH_TEST);
    // Clear the screen and depth buffer
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // // // Reset the matrix
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    //
    // const char* text1 = "PRESS SPACE";
    // glColor3ub(0,200,0);
    // glRasterPos2f(-0.1, 0);
	// for(int l=0; l<strlen(text1); l++)
	// 	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text1[l]);
    //
    // draw2DAxis(2,-1);
    //
    // glBegin(GL_LINES);
    //     glColor3ub(200,200,0);
    //     glVertex2f(-0.1, 0.1);
    //     glVertex2f( 0.1, 0.1);
    // glEnd();

    //globals::textHandler->drawText("Test: <>,.;:()!@#$%&*-+\\|/'\"");
    // globals::textHandler->drawText("AaBbCcDdEeFfGgHhIiJjKkLl");

    // ----- Stop Drawing Stuff! ------
    glfwSwapBuffers(gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
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
    gameWindow = glfwCreateWindow(globals::windowWidth,globals::windowHeight,windowTitle, NULL, NULL);
    if(gameWindow == NULL)
    {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(gameWindow);
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
    glfwSetCursorPos(gameWindow,globals::midWindowX, globals::midWindowY);
    // Call our initGame function to set up our OpenGL options
    initGame();
    // Specify the function which should execute when the mouse is moved
    glfwSetCursorPosCallback(gameWindow,handleMouseMove);
    // Specify the function which should execute when a mouse button is pressed or released
    glfwSetMouseButtonCallback(gameWindow, handleMouseButton);

    globals::started = false;
    globals::paused = true;
	glfwSetKeyCallback(gameWindow,handleKeypressMenu);
    // glDisable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(gameWindow) && !globals::started)
    {
        drawMain();
        // Check for any OpenGL errors (providing the location we called the function from)
        checkGLError("Main loop");
    }
    glEnable(GL_DEPTH_TEST);
	// Specify the function which should execute when a key is pressed or released
	glfwSetKeyCallback(gameWindow,handleKeypress);

    globals::paused = false;
    while (!glfwWindowShouldClose(gameWindow))
    {
        if(globals::paused){
            drawPaused();
        }else{
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
