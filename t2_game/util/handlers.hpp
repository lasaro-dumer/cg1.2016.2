#ifndef handlersH
#define handlersH
#include <GLFW/glfw3.h>      // Include OpenGL Framework library
// Function to deal with mouse position changes, called whenever the mouse cursorm moves
void handleMouseMove(GLFWwindow* window, double mouseX, double mouseY);
void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
// Function to set flags according to which keys are pressed or released
void handleKeypress(GLFWwindow* window, int theKey, int scancode, int theAction, int mods);
#endif
