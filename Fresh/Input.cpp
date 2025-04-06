#include "Input.h"

std::bitset<26> Input::isLetterPressed;
std::bitset<10> Input::isNumberPressed;
std::unordered_map<int, bool> Input::specialKeyForIsPressed = {
	{GLFW_KEY_SPACE, false},{GLFW_MOUSE_BUTTON_1, false}, {GLFW_MOUSE_BUTTON_2, false},
	{GLFW_KEY_ESCAPE, false}, {GLFW_KEY_BACKSPACE, false}, {GLFW_KEY_LEFT_CONTROL,false},
	{GLFW_KEY_LEFT_SHIFT, false},{GLFW_KEY_ENTER, false}, {GLFW_KEY_TAB, false},
	{GLFW_KEY_EQUAL, false},{GLFW_KEY_MINUS, false},
};
glm::vec2 Input::mousePos;

bool Input::IsKeyPressed(int key) {
	if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		return isLetterPressed.test(key - GLFW_KEY_A);
	else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
		return isNumberPressed.test(key - GLFW_KEY_0);
	else return specialKeyForIsPressed.at(key);
}
int Input::GetKeyAction(GLFWwindow* window, int key) {
	if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		return glfwGetKey(window, key - GLFW_KEY_A);
	else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
		return glfwGetKey(window, key - GLFW_KEY_0);
}

void Input::OnKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z)
		isLetterPressed.set(key - GLFW_KEY_A, action != GLFW_RELEASE);
	else if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
		isNumberPressed.set(key - GLFW_KEY_0, action != GLFW_RELEASE);
	else specialKeyForIsPressed.at(key) = (action != GLFW_RELEASE);
}
void Input::OnMouseButtonInput(GLFWwindow* window, int button, int action, int mods) {
	specialKeyForIsPressed.at(button) = (action != GLFW_RELEASE);
}
void Input::OnMouseMove(GLFWwindow* window, double x, double y) {
	mousePos = glm::vec2(x, y);
}
void Input::OnWindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Input::GetKeyInput(GLFWwindow* window) {
	glfwSetKeyCallback(window, Input::OnKeyInput);
}
void Input::GetMouseButtonInput(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, Input::OnMouseButtonInput);
}
void Input::GetMousePosition(GLFWwindow* window) { 
	glfwSetCursorPosCallback(window, Input::OnMouseMove);
}
void Input::GetWindowResize(GLFWwindow* window) {
	glfwSetWindowSizeCallback(window, Input::OnWindowResize);
}

void Input::GetKeyInput(GLFWwindow* window, void (*OnKey)(GLFWwindow* window, int key, int scancode, int action, int mods)) 
{
	glfwSetKeyCallback(window, OnKey);
}
void Input::GetMouseButtonInput(GLFWwindow* window, void (*OnMouseButt)(GLFWwindow* window, int button, int action, int mods))
{
	glfwSetMouseButtonCallback(window, OnMouseButt);
}
void Input::GetMousePosition(GLFWwindow* window, void(*OnMouseMove)(GLFWwindow* window, double x, double y))
{
	glfwSetCursorPosCallback(window, OnMouseMove);
}
void Input::GetWindowResize(GLFWwindow* window, void (*OnWindowResize)(GLFWwindow* window, int width, int height))
{
	glfwSetWindowSizeCallback(window, OnWindowResize);
}

void Input::HandleInput() {
	glfwPollEvents();
}
void Input::WaitInput() {
	glfwWaitEvents();
}

