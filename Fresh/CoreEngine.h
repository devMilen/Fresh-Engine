#pragma once
#include "glew.h"
#include "glfw3.h"
#include <assert.h>
#include "Sprite.h"
#include "Input.h"
#include "Time.h"

#define CREATEWINDOW GLFWwindow* window = CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "name"); 
#define MAIN \
int main() {\
    glfwMaximizeWindow(window);\
    glEnable(GL_DEPTH_TEST);\
    glDepthFunc(GL_LESS);\
	Start();\
    while (!glfwWindowShouldClose(window))\
    {\
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);\
        Time::Update();\
        Update();\
        glfwSwapBuffers(window);\
\
        glfwPollEvents();\
        Input::GetKeyInput(window);\
        Input::GetMouseButtonInput(window);\
        Input::GetMousePosition(window);\
    }\
CloseWindow();\
}

GLFWwindow* CreateWindow(unsigned int windowWidthPx, unsigned int windowHeightPx, const char* windowName);
void CloseWindow();
void Start();
void Update();
