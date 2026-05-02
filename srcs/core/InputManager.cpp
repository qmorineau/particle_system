#include "InputManager.hpp"
#include "Application.hpp"
#include "Camera.hpp"

// Callbacks
void InputManager::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) 
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		InputContext& ctx = app->inputContext();
		ctx.mouseMoved = true;
		ctx.mousePos.x = xposIn;
		ctx.mousePos.y = yposIn;
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		InputContext& ctx = app->inputContext();
		ctx.mouseScrolled = true;
		ctx.mouseOffset.x = xoffset;
		ctx.mouseOffset.y = yoffset;
	}
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) scancode /* physical position of a key, not keyboard dependent */;
	(void) mods; /* bitmask if mod is press, shift, ctrl, alt, super... */

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app)
		return;

	if (action == GLFW_PRESS)
		app->inputContext().keys[key] = true;
    else if (action == GLFW_RELEASE)
		app->inputContext().keys[key] = false;

	if (action == GLFW_RELEASE)
		app->inputHandler().handleKeysCallback(app, key);
}
