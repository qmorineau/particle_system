#include "Application.hpp"

Application::Application(char* arg) :
	_window(this),
	_scene(nullptr),
	_renderer()
{
	int particles = 1000000;
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

		// grtavity point from mouse pos
		vec3 pos = _scene->camera().getPosition() + _scene->camera().getFront() * 50;
		// float x = (2.0f * _inputContext.mouseX) / SCR_WIDTH - 1.0f;
		// float y = 1.0f - (2.0f * _inputContext.mouseY) / SCR_WIDTH;
		// float z = 1.0f;
		// vec3 rayNDC(x, y, z);
		// vec4 rayClip(x, y, -1.f, 1.f);
		// vec4 rayEye = glm::inverse(projection) * rayClip;
		_scene->setGravityPos(pos);
		// end of it
		_scene->update(_deltaTime);

		_simulation.simulate(*_scene, _deltaTime);
		
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

void Application::setShape(Simulation::Shape shape)
{
	_simulation.setShape(*_scene, shape);
}