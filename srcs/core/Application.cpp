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
	_scene = std::make_unique<Scene>(particles);
}
		

Application::~Application() {}

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
		_inputHandler.handleMouseCallback(this, InputHandler::CommandID::CMD_MOUSE_MOVE);
		if (_inputContext.mouseScrolled)
		_inputHandler.handleMouseCallback(this, InputHandler::CommandID::CMD_MOUSE_SCROLL);
		_inputHandler.handleKeys(this);
		
		// Frame / Delta
		float currentFrame = static_cast<float>(glfwGetTime());
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;
		
		// dynamic title
		_window.manageTitle(buildTitle());
		
		_simulation.simulate(_scene->simulationState(), _scene->particleSystem(), _deltaTime);
		_scene->update(_deltaTime, _inputContext.ndc);
		
		_renderer.beginFrame();
		_renderer.draw(_scene->simulationState(), _scene->particleSystem());
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
	_simulation.setShape(_scene->simulationState(), _scene->particleSystem(), shape);
}

std::string Application::buildTitle()
{
	std::string title = "Particles System ";
	const SimulationState& state = scene().simulationState();
	float fps = 1.f / std::max(_deltaTime, 0.0001f);
	std::string strFps = std::to_string(static_cast<int>(fps));
	title.append("[" + strFps + " fps]");
	std::string speed = std::to_string(static_cast<int>(state.timeSpeed() * 100));
	title.append("	- Speed: " + speed + "%");
	std::string gravityState(state.isGravity() ? "On" : "Off");
	title.append(" - Gravity: " + gravityState);
	std::string emitterState(state.isEmitter() ? "On" : "Off");
	title.append(" - Emitter: " + emitterState);
	if (_window.getMouse() 
		&& state.mouseTarget() != SimulationState::MouseTarget::Camera 
		&& state.mouseTarget() != SimulationState::MouseTarget::Free)
	{
		std::string str;
		SimulationState::MouseTarget tmp = state.mouseTarget();
		if (tmp == SimulationState::MouseTarget::Gravity)
			str = "Gravity";
		else
			str = "Emitter";
		title.append(" - [Moving: " + str + " position]");
	}
	title.append(" - Particles: " + std::to_string(_scene->simulationState().count() / 1000) + "k");
	return title;
}