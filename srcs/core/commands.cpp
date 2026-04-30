#include "commands.hpp"
#include "Application.hpp"

void Commands::CloseWindow::execute(Application* app) const
{
	app->closeWindow();
};

void Commands::MouseMove::execute(Application* app) const
{
	InputContext& ctx = app->inputContext();
	app->scene()->camera().onMouseMove(ctx.mouseX, ctx.mouseY);
};

void Commands::MouseScroll::execute(Application* app) const
{
	InputContext& ctx = app->inputContext();
	app->scene()->camera().onMouseScroll(ctx.mouseOffsetX, ctx.mouseOffsetY);
};

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