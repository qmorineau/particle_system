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

	setShape(Simulation::Shape::Sphere);
	while (!glfwWindowShouldClose(_window.getWindow()))
	{
		// world space pos from mouse pos
		vec2 NDC(
			(2.0f * _inputContext.mousePos.x) / SCR_WIDTH - 1.0f,
			1.0f - (2.0f * _inputContext.mousePos.y) / SCR_HEIGHT
		); // Normal Device Coordinate

		// Mouse
		if (_inputContext.mouseMoved)
		_inputHandler.handleMouseCallback(this, InputHandler::CommandID::CMD_MOUSE_MOVE);
		if (_inputContext.mouseScrolled)
		_inputHandler.handleMouseCallback(this, InputHandler::CommandID::CMD_MOUSE_SCROLL);
		_inputHandler.handleKeys(this);
		
		// Frame / Delta
		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
		
		// dynamic title
		_window.manageTitle(*this);
		
		_simulation.simulate(*_scene, NDC, _deltaTime);
		_scene->update(_deltaTime, NDC);
		
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
    ctx.mouseOffset.x = 0;
    ctx.mouseOffset.y = 0;
}

void Application::setShape(Simulation::Shape shape)
{
	_simulation.setShape(*_scene, shape);
}