#pragma once
#include "glew.h"
#include "glfw3.h"
#include <assert.h>
#include "Sprite.h"

#define CREATEWINDOW(windowWidth1, windowHeight1) GLFWwindow* window = CreateWindow(windowWidth1, windowHeight1, "name"); 
#define MAIN \
int main() {\
    glfwGetWindowSize(window, &windowWidth, &windowHeight);\
    glfwMaximizeWindow(window);\
	Start();\
    while (!glfwWindowShouldClose(window))\
    {\
        glClear(GL_COLOR_BUFFER_BIT);\
        Time::Update();\
         Update();\
        glfwSwapBuffers(window);\
\
        glfwPollEvents();\
    }\
CloseWindow();\
}

static int windowWidth, windowHeight;

GLFWwindow* CreateWindow(unsigned int windowWidthPx, unsigned int windowHeightPx, const char* windowName);
void CloseWindow();
void Start();
void Update();