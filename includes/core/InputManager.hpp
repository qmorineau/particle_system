#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class Application;
class LightManager;

class InputManager
{
	public:
		InputManager() {};
		~InputManager() {};

		void		handleKeys(Application* app);
		void		setKey(int key, bool state) {_keys[key] = state;};
		// Callbacks
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		// Dispatch Tables
		using Handler = void (InputManager::*)(Application*);
 		static const std::unordered_map<int, Handler> lightHandlers;
		static const std::unordered_map<int, Handler> handlers;

		// Handlers
		void closeWindow(Application *);
		void rotateX(Application *);
		void rotateY(Application *);
		void rotateZ(Application *);
		void resetCam(Application *);

	private:
		bool _keys[1024] = {false};
};

#endif