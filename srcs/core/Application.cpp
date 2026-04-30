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
		// Mouse
		if (_inputContext.mouseMoved)
			_inputHandler.handleMouseMove(this);
		if (_inputContext.mouseScrolled)
			_inputHandler.handleMouseScroll(this);

		// Frame / Delta
		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		
		_window.manageTitle(*this);
		glfwSetKeyCallback(_window.getWindow(), InputManager::keyCallback);
		_inputHandler.handleKeys(this);
		_scene->update(_deltaTime);

		if (!i && ++i)
			_simulation.setShape(_scene->particles(), _scene->getParticles(), Simulation::Shape::Cube);
		_simulation.simulate(_scene->particles(), _scene->getParticles(), _deltaTime);
		
		_renderer.beginFrame();
		_renderer.draw(_scene);

		endFrame();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window.getWindow());
        glfwPollEvents();
	}
}

void Application::endFrame()
{
    auto& ctx = _inputContext;
    ctx.mouseMoved = false;
    ctx.mouseScrolled = false;
    ctx.mouseOffsetX = 0;
    ctx.mouseOffsetY = 0;
}