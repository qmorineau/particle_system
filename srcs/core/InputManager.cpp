#include "InputManager.hpp"
#include "Application.hpp"
#include "Camera.hpp"

void InputManager::handleKeys(Application* app)
{
	Camera& camera = app->getCamera();
	if (_keys[GLFW_KEY_W])
		camera.processKeyboard(Camera::FORWARD, app->getDelta());
	if (_keys[GLFW_KEY_S])
		camera.processKeyboard(Camera::BACKWARD, app->getDelta());
	if (_keys[GLFW_KEY_A])
		camera.processKeyboard(Camera::LEFT, app->getDelta());
	if (_keys[GLFW_KEY_D])
		camera.processKeyboard(Camera::RIGHT, app->getDelta());
};


// Key Handlers

const std::unordered_map<int, InputManager::Handler> InputManager::handlers =
{
	{GLFW_KEY_ESCAPE, &InputManager::closeWindow},
	{GLFW_KEY_X, &InputManager::rotateX},
	{GLFW_KEY_Y, &InputManager::rotateY},
	{GLFW_KEY_Z, &InputManager::rotateZ},
	{GLFW_KEY_R, &InputManager::resetCam}
};

void InputManager::closeWindow(Application* app)			{app->closeWindow();}
void InputManager::rotateX(Application* app)		{app->scene()->rotateX();}
void InputManager::rotateY(Application* app)		{app->scene()->rotateY();}
void InputManager::rotateZ(Application* app)		{app->scene()->rotateZ();}
void InputManager::resetCam(Application* app)
{
	app->getCamera().resetPosition();
	app->scene()->resetRot();
}

// Callbacks

void InputManager::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
	    app->getCamera().onMouseMove(xposIn, yposIn);
}

void InputManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app)
		app->getCamera().onMouseScroll(xoffset, yoffset);
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void) scancode /* physical position of a key, not keyboard dependent */;
	(void) mods; /* bitmask if mod is press, shift, ctrl, alt, super... */

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app)
		return;

	if (action == GLFW_PRESS) {app->setKey(key, true);}
    else if (action == GLFW_RELEASE) {app->setKey(key, false);}

	if (action == GLFW_RELEASE)
	{
		
		auto iterator = handlers.find(key);
		if (iterator == handlers.end())
			return;
		Handler h = iterator->second;
		(app->inputManager().*h)(app);
	}
}
