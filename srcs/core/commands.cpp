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
	InputContext& ctx = app->inputContext();
	app->scene()->camera().onMouseMove(ctx.mouseX, ctx.mouseY);
};

void Commands::MouseScroll::execute(Application* app) const
{
	InputContext& ctx = app->inputContext();
	app->getCamera().onMouseScroll(ctx.mouseOffsetX, ctx.mouseOffsetY);
};

void Commands::ToggleMouse::execute(Application* app) const
{
	app->window().toggleMouse();
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
	app->scene()->toggleGravity();
};
