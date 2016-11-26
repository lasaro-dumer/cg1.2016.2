#include <GLee.h>         // No need to link to GL/gl.h
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
#include <iostream>
#include <pthread.h>
#include "handlers.hpp"
#include "globals.hpp"
#include "../elements/shoot.hpp"
// Function to deal with mouse position changes, called whenever the mouse cursorm moves
void handleMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
    if(!globals::paused){
        double horizMovement = mouseX - globals::midWindowX;
        double vertMovement  = mouseY - globals::midWindowY;
        globals::cameraFPS->rotate(vertMovement,horizMovement);
        // Reset the mouse position to the centre of the window each frame
        glfwSetCursorPos(window, globals::midWindowX, globals::midWindowY);
    }
}

void handleMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    // std::cout << "mouse: button=" << button << " action=" << action << " mods=" << mods;
    if (!globals::paused && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        shoot* s = new shoot(globals::cameraFPS->getCurrentPosition(),globals::modelObjs["shoot1"],5,globals::gameOptions.getShootSpeed());
        globals::shoots.push_back(s);
        pthread_t ts;
	    pthread_create(&ts, NULL, audio::tryPlaySoundAsync, globals::sounds["laser1"]);
    }
    else if (!globals::paused && button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){
            shoot* s = new shoot(globals::cameraFPS->getCurrentPosition(),globals::modelObjs["shoot2"],100,globals::gameOptions.getShootSpeed(1));
            globals::shoots.push_back(s);
            pthread_t ts;
    	    pthread_create(&ts, NULL, audio::tryPlaySoundAsync, globals::sounds["laser2"]);
        }
        else if(action == GLFW_RELEASE){
            // std::cout << " released right";
        }
    }
    // std::cout << std::endl;
}

// Function to set flags according to which keys are pressed or released
void handleKeypress(GLFWwindow* window, int theKey, int scancode, int theAction, int mods)
{
    /*
    2 = LEFT CTRL
    4 = LEFT ALT
    */
    int lightMod = 2;
    // If a key is pressed, toggle the relevant key-press flag
    if (theAction == GLFW_PRESS || theAction == GLFW_REPEAT)
    {
        switch(theKey)
        {
            case GLFW_KEY_W:
                if(mods == lightMod) globals::lightPos[2]+=0.5;
                else globals::cameraFPS->setMoveForward(true);
                break;
            case GLFW_KEY_S:
                if(mods == lightMod) globals::lightPos[2]-=0.5;
                else globals::cameraFPS->setMoveBackward(true);
                break;
            case GLFW_KEY_A:
                if(mods == lightMod) globals::lightPos[0]+=0.5;
                else globals::cameraFPS->setMoveLeft(true);
                break;
            case GLFW_KEY_D:
                if(mods == lightMod) globals::lightPos[0]-=0.5;
                else globals::cameraFPS->setMoveRight(true);
                break;
            case GLFW_KEY_SPACE:
                if(mods == lightMod) globals::lightPos[1]+=0.5;
                else globals::cameraFPS->setMoveUp(true);
                break;
            case GLFW_KEY_LEFT_SHIFT:
                if(mods == lightMod) globals::lightPos[1]-=0.5;
                else globals::cameraFPS->setMoveDown(true);
                break;
            case GLFW_KEY_F1:           globals::setFullScreen(!globals::fullScreenMode);     break;
            case GLFW_KEY_ESCAPE:       glfwSetWindowShouldClose(window, true); break;
            case GLFW_KEY_P:
                if(globals::paused){
                    glfwSetCursorPos(window, globals::midWindowX, globals::midWindowY);
                    globals::cameraFPS->setPerspective(globals::windowHeight,globals::windowWidth);
                }
                globals::paused = !globals::paused;
                break;
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
            case GLFW_KEY_W:            globals::cameraFPS->setMoveForward(false);    break;
            case GLFW_KEY_S:            globals::cameraFPS->setMoveBackward(false);   break;
            case GLFW_KEY_A:            globals::cameraFPS->setMoveLeft(false);       break;
            case GLFW_KEY_D:            globals::cameraFPS->setMoveRight(false);      break;
            case GLFW_KEY_SPACE:        globals::cameraFPS->setMoveUp(false);          break;
            case GLFW_KEY_LEFT_SHIFT:   globals::cameraFPS->setMoveDown(false);        break;
            default:
                /*Do nothing...*/
                std::cout << "REL KEY: " << theKey << std::endl;
                break;
        }
    }
}

// Function to set flags according to which keys are pressed or released
void handleKeypressMenu(GLFWwindow* window, int theKey, int scancode, int theAction, int mods)
{
    // If a key is pressed, toggle the relevant key-press flag
    if (theAction == GLFW_PRESS || theAction == GLFW_REPEAT)
    {
        switch(theKey)
        {
            case GLFW_KEY_SPACE:
                if(!globals::started){
                    globals::started = true;
                    glfwSetCursorPos(window, globals::midWindowX, globals::midWindowY);
                    globals::cameraFPS->setPerspective(globals::windowHeight,globals::windowWidth);
                }
                break;
            case GLFW_KEY_F1:           globals::setFullScreen(!globals::fullScreenMode);     break;
            case GLFW_KEY_ESCAPE:       glfwSetWindowShouldClose(window, true); break;
            default:
                /*Do nothing...*/
                std::cout << "PRE KEY: " << theKey << std::endl;
                break;
        }
    }
}
