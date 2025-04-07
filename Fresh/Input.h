#pragma once
#include "glfw3.h"
#include <bitset>

#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <unordered_map>

class Input {
public:
	static std::bitset<26> isLetterPressed;
	static std::bitset<10> isNumberPressed;
	static std::unordered_map<int, bool> specialKeyForIsPressed;
	static glm::vec2 mousePos;

	static void OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods);
	static void OnMouseMove(GLFWwindow* window, double x, double y);
	static void OnWindowResize(GLFWwindow* window, int width, int height);

	static void GetKeyInput(GLFWwindow* window);
	static void GetMouseButtonInput(GLFWwindow* window);
	static void GetMousePosition(GLFWwindow* window);
	static void GetWindowResize(GLFWwindow* window);

	static void GetKeyInput(GLFWwindow* window, void (*OnKey)(GLFWwindow* window, int key, int scancode, int action, int mods));
	static void GetMouseButtonInput(GLFWwindow* window, void (*OnMouseButt)(GLFWwindow* window, int button, int action, int mods));
	static void GetMousePosition(GLFWwindow* window, void(*OnMouseMove)(GLFWwindow* window, double x, double y));
	static void GetWindowResize(GLFWwindow* window, void (*OnWindowResize)(GLFWwindow* window, int width, int height));

	static void HandleInput();
	static void WaitInput();

	static bool IsKeyPressed(int key);
	static int GetKeyAction(GLFWwindow* window, int key);
};

