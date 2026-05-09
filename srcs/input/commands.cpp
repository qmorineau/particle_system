#include "commands.hpp"
#include "Application.hpp"

// Window
void Commands::CloseWindow::execute(Application* app) const
{
	app->window().closeWindow();
};
// Mouse
void Commands::MouseMove::execute(Application* app) const
{
	if (!app->window().getMouse())
	{	
		InputContext& ctx = app->inputContext();
		app->scene().camera().onMouseMove(ctx.mousePos.x, ctx.mousePos.y);
	}
};

void Commands::MouseScroll::execute(Application* app) const
{
	InputContext& ctx = app->inputContext();
	app->getCamera().onMouseScroll(ctx.mouseOffset.x, ctx.mouseOffset.y);
};
void Commands::EnableMouse::execute(Application* app) const
{
	app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Free);
	app->window().enableMouse();
};
void Commands::DisableMouse::execute(Application* app) const
{
	app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Camera);
	app->getCamera().disableMouse();
	glfwSetCursorPos(app->window().getWindow(), SCR_WIDTH / 2, SCR_HEIGHT / 2);
	app->window().disableMouse();
};
// Camera
void Commands::CameraForward::execute(Application* app) const
{
	app->getCamera().processKeyboard(Camera::FORWARD, app->getDelta());
};

void Commands::CameraBackward::execute(Application* app) const
{
	app->getCamera().processKeyboard(Camera::BACKWARD, app->getDelta());
};

void Commands::CameraLeft::execute(Application* app) const
{
	app->getCamera().processKeyboard(Camera::LEFT, app->getDelta());
};

void Commands::CameraRight::execute(Application* app) const
{
	app->getCamera().processKeyboard(Camera::RIGHT, app->getDelta());
};
void Commands::CameraReset::execute(Application* app) const
{
	app->getCamera().resetPosition();
};
// Shape
void Commands::SetCubeShape::execute(Application* app) const
{
	app->setShape(Simulation::Shape::Cube);
};
void Commands::SetSphereShape::execute(Application* app) const
{
	app->setShape(Simulation::Shape::Sphere);
};
// Simulation
void Commands::ToggleGravity::execute(Application* app) const
{
	app->scene().simulationState().toggleGravity();
};
void Commands::ToggleEmitter::execute(Application* app) const
{
	if (app->window().getMouse())
		app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Emitter);
	app->scene().simulationState().toggleEmitter();
};
void Commands::SlowTime::execute(Application* app) const
{
	app->scene().simulationState().slowTimeSpeed();
};
void Commands::AccelerateTime::execute(Application* app) const
{
	app->scene().simulationState().accelerateTimeSpeed();
};
void Commands::ChangeColorMode::execute(Application* app) const
{
	app->scene().simulationState().changeColorMode();
};
void Commands::MoveGravity::execute(Application* app) const
{
	if (app->window().getMouse())
	{
		if (app->scene().simulationState().mouseTarget() == SimulationState::MouseTarget::Gravity)
			app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Free);
		else
			app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Gravity);
	}
};
void Commands::MoveEmitter::execute(Application* app) const
{
	if (app->window().getMouse())
	{
		if (app->scene().simulationState().mouseTarget() == SimulationState::MouseTarget::Emitter)
			app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Free);
		else
			app->scene().simulationState().setMouseTarget(SimulationState::MouseTarget::Emitter);
	}
};
void Commands::AddParticles::execute(Application* app) const
{
	app->scene().simulationState().addParticles();
};
void Commands::RemoveParticles::execute(Application* app) const
{
	app->scene().simulationState().removeParticles();
};