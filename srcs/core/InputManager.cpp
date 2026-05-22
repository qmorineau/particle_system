#include "InputManager.hpp"
#include "Application.hpp"
#include "Camera.hpp"

// Mouse
void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		InputContext& ctx = app->inputContext();
		ctx.setMods(mods);
		if (action == GLFW_PRESS)
		{
			ctx.pressMouse(button);
			app->inputHandler().onMouseEvent(app, button);
		}
		else if (action == GLFW_RELEASE)
		{
			ctx.releaseMouse(button);
		}
	}
}

void InputManager::mouseCallback(GLFWwindow* window, double xposIn, double yposIn) 
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		InputContext& ctx = app->inputContext();
		ctx.setIsMouseMoved(true);
		ctx.setMousePos(vec2(xposIn, yposIn));
		ctx.setNDC(vec2(
			(2.0f * xposIn) / SCR_WIDTH - 1.0f,
			1.0f - (2.0f * yposIn) / SCR_HEIGHT
		));
	}
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	{
		InputContext& ctx = app->inputContext();
		ctx.setIsMouseScrolled(true);
		ctx.setMouseScrolled(vec2(xoffset, yoffset));
	}
}

// Keyboard
// scancode: physical position of a key, not keyboard dependent
// mods: bitmask if mod is press (shift, ctrl, alt, super...)
void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) scancode;
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app)
		return;

	InputContext& ctx = app->inputContext();
	ctx.setMods(mods);
	if (action == GLFW_PRESS)
	{
		ctx.pressKey(key);
		app->inputHandler().onKeyPressed(app, key);
	}
    else if (action == GLFW_RELEASE)
	{
		ctx.releaseKey(key);
	}
}
