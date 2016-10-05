#include <iostream>

#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <GL/freeglut.h>  // Include FreeGLUT so we can easily draw spheres and calculate our viewing frustrum
#include <math.h>         // Used only for sin() and cos() functions
#include <list>
#include <map>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "camera.hpp"
#include "elements/point3D.hpp"
#include "elements/colorRgb.hpp"
#include "elements/shoot.hpp"
#include "elements/modelObj.hpp"
#include "elements/asteroid.hpp"

using namespace std;

GLint windowWidth  = 1024;                    // Width of our window
GLint windowHeight = 768;                    // Heightof our window
GLint oldWindowWidth,oldWindowHeight;
GLint windowPosX   = 50;      // Windowed mode's top-left corner x
GLint windowPosY   = 50;      // Windowed mode's top-left corner y

GLint midWindowX = windowWidth  / 2;         // Middle of the window horizontally
GLint midWindowY = windowHeight / 2;         // Middle of the window vertically

bool fullScreenMode = false;

GLFWwindow* gameWindow;

// How many segments make up our sphere around the latutude and longitude of the sphere
// The higher the number, the closer an approximation to a sphere we get! Try low numbers to see how bad it looks!
int sphereLatitudalSegments  = 100;
int sphereLongitudalSegments = 100;

// Set the light source location to be the same as the sun position
// Don't forget that the position is a FOUR COMPONENT VECTOR (with the last component as w) if you omit the last component expect to get NO LIGHT!!!
// Learnt that one the hard way... =P
GLfloat  lightPos[] = { 0.0f, 0.0f, -300.0f, 1.0f };

// How fast we move (higher values mean we move and strafe faster)
GLfloat movementSpeedFactor = 3.0f;
GLfloat vertMouseSensitivity  = 10.0f;
GLfloat horizMouseSensitivity = 10.0f;
camera cameraFPS(vertMouseSensitivity,horizMouseSensitivity,movementSpeedFactor);

map<string,modelObj*> modelObjs;
list<shoot*> shoots;

char windowTitle[] = "Space Mission 3: Lost in Space";

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
    if(fullScreenMode == toFullScreen)
        return;
    fullScreenMode = toFullScreen;

    glfwGetWindowPos(gameWindow, &windowPosX, &windowPosY);
    GLFWmonitor* monitor = NULL;
    if (fullScreenMode) {                     // Full-screen mode
        monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        oldWindowWidth = windowWidth;
        oldWindowHeight = windowHeight;
        windowWidth = mode->width;
        windowHeight = mode->height;
    } else {                                         // Windowed mode
        windowWidth = oldWindowWidth;
        windowHeight = oldWindowHeight;
    }
    glfwSetWindowMonitor(gameWindow,monitor,windowPosX,windowPosY,windowWidth,windowHeight,GLFW_DONT_CARE);
    glfwSetWindowSize(gameWindow,windowWidth,windowHeight);
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
    cameraFPS.setPerspective(windowHeight,windowWidth);
}
asteroid* ast1;
asteroid* ast2;
void initGame()
{

    colorRgb* astColor = new colorRgb(160,100,20);
    modelObj* ast1Model = new modelObj(astColor,false);
    ast1Model->loadFromFile("data/models/asteroid1.obj");
    modelObjs["asteroid1"] = ast1Model;

    ast1 = new asteroid(modelObjs["asteroid1"],new point3D(50,0,50),1000.0f);
    ast1->setSpeed(0);
    ast2 = new asteroid(modelObjs["asteroid1"],new point3D(0,0,0,1,1,1),100.0f);
    // ----- GLFW Settings -----
    glfwSetInputMode(gameWindow,GLFW_CURSOR,GLFW_CURSOR_DISABLED); // Hide the mouse cursor
    // ----- Window and Projection Settings -----
    // Setup our viewport to be the entire size of the window
    glViewport(0, 0, (GLsizei)windowWidth, (GLsizei)windowHeight);
    cameraFPS.setPerspective(windowHeight,windowWidth);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ----- OpenGL settings -----
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set out clear colour to black, full alpha
    glfwSwapInterval(1);        // Lock to vertical sync of monitor (normally 60Hz, so 60fps)
    glShadeModel(GL_SMOOTH);    // Enable (gouraud) shading
    glEnable(GL_DEPTH_TEST);    // Enable depth testing
    glClearDepth(1.0f);         // Clear the entire depth of the depth buffer
    glDepthFunc(GL_LEQUAL);		// Set our depth function to overwrite if new value less than or equal to current value
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Ask for nicest perspective correction
    glEnable(GL_CULL_FACE); // Do not draw polygons facing away from us
    glLineWidth(2.0f);			// Set a 'chunky' line width

    // ---- Set up OpenGL lighting -----
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Ambient, diffuse and specular lighting values (note that these are ALL FOUR COMPONENT VECTORS!)
    GLfloat  ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLint specularMagnitude = 64; // Define how "tight" our specular highlights are (larger number = smaller specular highlight). The valid range is is 1 to 128
    // Setup and enable light 0
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);          // Specify the position of the light
    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambientLight);      // Specify ambient light properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuseLight);      // Specify diffuse light properties
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);     // Specify specular light properties
    glEnable(GL_LIGHT0);

    // Enable colour tracking of materials
    glEnable(GL_COLOR_MATERIAL);
    // Define the shininess of the material we'll use to draw things
    GLfloat materialSpecularReflectance[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // Use our shiny material and magnitude
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularReflectance);
    glMateriali(GL_FRONT, GL_SHININESS, specularMagnitude);

    // Check for any OpenGL errors (providing the location we called the function from)
    checkGLError("initGame");
}

// Function to deal with mouse position changes, called whenever the mouse cursorm moves
void handleMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
    double horizMovement = mouseX - midWindowX;
    double vertMovement  = mouseY - midWindowY;
    cameraFPS.rotate(vertMovement,horizMovement);
    // Reset the mouse position to the centre of the window each frame
    glfwSetCursorPos(gameWindow, midWindowX, midWindowY);
}

void handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        shoots.push_back(new shoot(cameraFPS.getCurrentPosition(),new colorRgb(255,60,0)));
    }
}

// Function to set flags according to which keys are pressed or released
void handleKeypress(GLFWwindow* window, int theKey, int scancode, int theAction, int mods)
{
    // If a key is pressed, toggle the relevant key-press flag
    if (theAction == GLFW_PRESS || theAction == GLFW_REPEAT)
    {
        switch(theKey)
        {
            case GLFW_KEY_W:            cameraFPS.setMoveForward(true);     break;
            case GLFW_KEY_S:            cameraFPS.setMoveBackward(true);    break;
            case GLFW_KEY_A:            cameraFPS.setMoveLeft(true);        break;
            case GLFW_KEY_D:            cameraFPS.setMoveRight(true);       break;
            case GLFW_KEY_SPACE:        cameraFPS.setMoveUp(true);          break;
            case GLFW_KEY_LEFT_SHIFT:   cameraFPS.setMoveDown(true);        break;
            case GLFW_KEY_F1:           setFullScreen(!fullScreenMode);     break;
            case GLFW_KEY_ESCAPE:       glfwSetWindowShouldClose(window, true); break;
            default:
                /*Do nothing...*/
                std::cout << "PRE KEY: " << theKey << std::endl;
                break;
        }
    }
    else // If a key is released, toggle the relevant key-release flag
    {
        switch(theKey)
        {
            case GLFW_KEY_W:            cameraFPS.setMoveForward(false);    break;
            case GLFW_KEY_S:            cameraFPS.setMoveBackward(false);   break;
            case GLFW_KEY_A:            cameraFPS.setMoveLeft(false);       break;
            case GLFW_KEY_D:            cameraFPS.setMoveRight(false);      break;
            case GLFW_KEY_SPACE:        cameraFPS.setMoveUp(false);          break;
            case GLFW_KEY_LEFT_SHIFT:   cameraFPS.setMoveDown(false);        break;
            default:
                /*Do nothing...*/
                std::cout << "REL KEY: " << theKey << std::endl;
                break;
        }
    }
}

// Function to draw a grid of lines
void drawGround()
{
    GLfloat extent      = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
    GLfloat stepSize    = 20.0f;  // The size of the separation between points
    GLfloat groundLevel = -100.0f;   // Where on the Y-Axis the ground is drawn
    // Set colour to white
    glColor3ub(255, 255, 255);
    // Draw our ground grid
    glBegin(GL_LINES);
    for (GLint loop = -extent; loop < extent; loop += stepSize)
    {
        // Draw lines along Z-Axis
        glVertex3f(loop, groundLevel,  extent);
        glVertex3f(loop, groundLevel, -extent);
        // Draw lines across X-Axis
        glVertex3f(-extent, groundLevel, loop);
        glVertex3f(extent,  groundLevel, loop);
    }
    glEnd();
}

void drawAxis(GLfloat lineLength) {
    glBegin(GL_LINES);
        //Red positive X-Axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0,0,0);
        glVertex3f(lineLength,0,0);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(i,0,0);
            glVertex3f(i-2.5f,0,0);
        }
        //Blue positive Y-Axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0,0,0);
        glVertex3f(0,lineLength,0);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(0,i,0);
            glVertex3f(0,i-2.5f,0);
        }
        //Green positive Z-Axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0,0,0);
        glVertex3f(0,0,lineLength);
        for (GLfloat i = 0; i > -lineLength; i=i-5) {
            glVertex3f(0,0,i);
            glVertex3f(0,0,i-2.5f);
        }
    glEnd();
}

void draw3DRect(GLfloat faceSize, GLfloat depth) {
    glBegin(GL_QUADS);
        //Front face
        glVertex3f(       0,faceSize,0);
        glVertex3f(       0,       0,0);
        glVertex3f(faceSize,       0,0);
        glVertex3f(faceSize,faceSize,0);

        // glVertex3f(faceSize,faceSize,0);
        // glVertex3f(faceSize,       0,0);
        // glVertex3f(       0,       0,0);
        // glVertex3f(       0,faceSize,0);
        //Right face
        glVertex3f(faceSize,       0,0);
        glVertex3f(faceSize,       0,-depth);
        glVertex3f(faceSize,faceSize,-depth);
        glVertex3f(faceSize,faceSize,0);

        // glVertex3f(faceSize,faceSize,0);
        // glVertex3f(faceSize,faceSize,-depth);
        // glVertex3f(faceSize,       0,-depth);
        // glVertex3f(faceSize,       0,0);
        //Left face
        glVertex3f(       0,faceSize,0);
        glVertex3f(       0,faceSize,-depth);
        glVertex3f(       0,       0,-depth);
        glVertex3f(       0,       0,0);

        // glVertex3f(       0,       0,0);
        // glVertex3f(       0,       0,-depth);
        // glVertex3f(       0,faceSize,-depth);
        // glVertex3f(       0,faceSize,0);
        //Top face
        glVertex3f(faceSize,faceSize,0);
        glVertex3f(faceSize,faceSize,-depth);
        glVertex3f(       0,faceSize,-depth);
        glVertex3f(       0,faceSize,0);

        // glVertex3f(       0,faceSize,0);
        // glVertex3f(       0,faceSize,-depth);
        // glVertex3f(faceSize,faceSize,-depth);
        // glVertex3f(faceSize,faceSize,0);
        //Bottom face
        glVertex3f(       0,       0,0);
        glVertex3f(       0,       0,-depth);
        glVertex3f(faceSize,       0,-depth);
        glVertex3f(faceSize,       0,0);

        // glVertex3f(faceSize,       0,0);
        // glVertex3f(faceSize,       0,-depth);
        // glVertex3f(       0,       0,-depth);
        // glVertex3f(       0,       0,0);
        //Back face
        glVertex3f(faceSize,faceSize,-depth);
        glVertex3f(faceSize,       0,-depth);
        glVertex3f(       0,       0,-depth);
        glVertex3f(       0,faceSize,-depth);

        // glVertex3f(       0,faceSize,-depth);
        // glVertex3f(       0,       0,-depth);
        // glVertex3f(faceSize,       0,-depth);
        // glVertex3f(faceSize,faceSize,-depth);
    glEnd();
}

// Function to draw our spheres and position the light source
void drawScene()
{
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    cameraFPS.draw();

    // Define our light position
    // *** IMPORTANT! *** A light position takes a FOUR component vector! The last component is w! If you leave off the last component, you get NO LIGHT!!!
    GLfloat newLightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, newLightPos);  // Place the light where the sun is!

    //*
    // Draw the lower ground-grid
    drawGround();
    // Draw the upper ground-grid, keeping a copy of our current matrix on the stack before we translate it
    glPushMatrix();
    glTranslatef(0.0f, 200.0f, 0.0f);
    drawGround();
    glPopMatrix();

    drawAxis(300);

    glTranslatef(20,20,20);
    glColor3ub(255,255,0);
    draw3DRect(20,50);
    glTranslatef(-20,-20,-20);

    ast1->draw();
    ast2->draw();

    list<shoot*>::iterator is;
    for (is = shoots.begin(); is != shoots.end(); ++is) {
        if((*is)->isAlive()){
            (*is)->draw();
        }
        else
            is = shoots.erase(is);
    }

    // ----- Stop Drawing Stuff! ------
    glfwSwapBuffers(gameWindow); // Swap the buffers to display the scene (so we don't have to watch it being drawn!)
    glfwPollEvents();
}

// Fire it up...
int main(int argc, char **argv)
{
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
    gameWindow = glfwCreateWindow(windowWidth,windowHeight,windowTitle, NULL, NULL);
    if(gameWindow == NULL)
    {
        cout << "Failed to open window!" << endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(gameWindow);
    setFullScreen(fullScreenMode);// Will set viewport and camera perspective
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
    glfwSetCursorPos(gameWindow,midWindowX, midWindowY);
    // Call our initGame function to set up our OpenGL options
    initGame();
    // Specify the function which should execute when a key is pressed or released
    glfwSetKeyCallback(gameWindow,handleKeypress);
    // Specify the function which should execute when the mouse is moved
    glfwSetCursorPosCallback(gameWindow,handleMouseMove);
    // Specify the function which should execute when a mouse button is pressed or released
    glfwSetMouseButtonCallback(gameWindow, handleMouseButton);

    while (!glfwWindowShouldClose(gameWindow))
    {
        // Draw our scene
        drawScene();
        // Move our camera
        cameraFPS.move();
        // Check for any OpenGL errors (providing the location we called the function from)
        checkGLError("Main loop");
    }
    // Clean up GLFW and exit
    glfwTerminate();
    return 0;
}
