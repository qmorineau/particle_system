#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "InputManager.hpp"
#include "InputHandler.hpp"
#include "InputContext.hpp"
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
		void setShape(Simulation::Shape shape);
		
		// getter
		float			getDelta() 		{return _deltaTime;};
		Camera&			getCamera()		{return _scene->camera();};
		Renderer&		renderer() 		{return _renderer;};
		Scene&			scene() 		{return *_scene;};
		Window&			window()		{return _window;};
		InputManager&	inputManager()	{return _inputManager;};
		InputHandler&	inputHandler()	{return _inputHandler;};
		InputContext&	inputContext()	{return _inputContext;};
	private:
		Window					_window;
		InputManager			_inputManager;
		InputHandler			_inputHandler;
		InputContext			_inputContext;
		std::unique_ptr<Scene>	_scene;
		Renderer				_renderer;
		Simulation				_simulation;
		float					_deltaTime = 0.0f;
		float					_lastFrame = 0.0f;

		void 		initWindow();
		void		renderLoop();
		void 		endFrame();
		std::string buildTitle();
};

#endif