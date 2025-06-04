#pragma once
#include "glfw3.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <bitset>
#include <unordered_map>
#include<array>


class Input {
public:
	enum Action
	{
		NotPressed = 0, JustPressed = 1, Held = 2, JustReleased = 3
	};
	class Mouse
	{
	public:
		static glm::vec2 pos;
		static std::array<Action, 5> buttons;

		void static Move(float x, float y);
		void static Move(const glm::vec2& v);

		void static Set(float x, float y, Action newAction, int key);
		void static Set(const glm::vec2& pos, Action newAction, int key);

		void static SetPos(float x, float y);
		void static SetPos(const glm::vec2& pos);

		static void UpdateNoInput();
		static void UpdateWithInput(int button, int action);
	};

	static std::bitset<26> isLetterPressed;
	static std::bitset<10> isNumberPressed;
	static std::unordered_map<int, bool> specialKeyForIsPressed;

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

