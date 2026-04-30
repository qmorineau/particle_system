#include "Application.hpp"

Application::Application(char* arg) :
	_window(this),
	_scene(nullptr),
	_renderer()
{
	int particles = 3000000;
	if (arg)
	{
		int tmp = std::atoi(arg);
		if (tmp > 0)
			particles = tmp;
	}
	_scene = new Scene(particles);
}
		

Application::~Application()
{
	if (_scene)
		delete _scene;
}

void Application::run()
{		
	renderLoop();
}

void Application::renderLoop()
{
	// glfwSwapInterval(0); // disable vsync
	glfwSwapInterval(1); // cap framerate to monitor framerate

	int i = 0;
	while (!glfwWindowShouldClose(_window.getWindow()))
	{
		if (_mouseMoved)
		{
			_scene->camera().onMouseMove(_mouseX, _mouseY);

		}
		if (_mouseScrolled)
		{
			_scene->camera().onMouseScroll(_mouseOffsetX, _mouseOffsetY);
		}

		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		_window.manageTitle(*this);
		glfwSetKeyCallback(_window.getWindow(), InputManager::keyCallback);
		_inputManager.handleKeys(this);
		_scene->update(_deltaTime);

		if (!i && ++i)
			_simulation.setShape(_scene->particles(), _scene->getParticles(), Simulation::Shape::Cube);
		_simulation.simulate(_scene->particles(), _scene->getParticles(), _deltaTime);
		
		_renderer.beginFrame();
		_renderer.draw(_scene);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window.getWindow());
        glfwPollEvents();
	}
}
