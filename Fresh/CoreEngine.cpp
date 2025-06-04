#include "CoreEngine.h"

 GLFWwindow* CreateWindow(unsigned int windowWidthPx, unsigned int windowHeightPx, const char* windowName) {
     assert(glfwInit());

     //const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
     //GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Full-Screen Window", glfwGetPrimaryMonitor(), NULL);
     glfwWindowHint(GLFW_DEPTH_BITS, 24);

     GLFWwindow* window = glfwCreateWindow(windowWidthPx, windowHeightPx, windowName, NULL, NULL);
     assert(window);

     glfwMakeContextCurrent(window); 

     assert(glewInit() == GLEW_OK);  

     return window; 
 }
 void CloseWindow() {
     glfwTerminate();
 }
