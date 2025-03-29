#include "CoreEngine.h"

 GLFWwindow* CreateWindow(unsigned int windowWidthPx, unsigned int windowHeightPx, const char* windowName) {
     assert(glfwInit());

     GLFWwindow* window = glfwCreateWindow(windowWidthPx, windowHeightPx, windowName, NULL, NULL);
     assert(window);

     glfwMakeContextCurrent(window); 

     assert(glewInit() == GLEW_OK);  

     return window; 
 }
 void CloseWindow() {
     glfwTerminate();
 }
