#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include "InputManager.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Scene.hpp"
#include "Simulation.hpp"

class Application
{
	public:
		Application(char *args);
		~Application();
		void run();
		void closeWindow() {_window.closeWindow();};
		
		// getter
		float			getDelta() {return _deltaTime;};
		Camera&			getCamera() {return _scene->camera();};
		Renderer&		renderer() {return _renderer;};
		Scene*			scene() {return _scene;};
		InputManager&	inputManager() {return _inputManager;};
		// setter
		void 			setMousePosition(double x, double y) {_mouseX = x; _mouseY = y; _mouseMoved = true;};
		void 			setMouseScroll(double x, double y) {_mouseOffsetX= x; _mouseOffsetY = y; _mouseScrolled = true;};
		void 			setKey(int key, bool state) {_inputManager.setKey(key, state);};

	private:
		Window				_window;
		InputManager		_inputManager;
		Scene*				_scene;
		Renderer			_renderer;
		Simulation			_simulation;
		float				_deltaTime = 0.0f;
		float				_lastFrame = 0.0f;
		double				_mouseX = 0;
		double				_mouseY = 0;
		bool				_mouseMoved = false;
		double				_mouseOffsetX = 0;
		double				_mouseOffsetY = 0;
		bool				_mouseScrolled = false;

		void initWindow();
		void applyRotation();
		void renderLoop();
		void manageWindowTitle();
};

#endif