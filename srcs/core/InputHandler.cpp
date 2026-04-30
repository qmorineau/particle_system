#include "InputHandler.hpp"
#include "commands.hpp"
#include "Application.hpp"

InputHandler::InputHandler()
{
	// Key Press
	_eventCommand[CMD_MOUSE_MOVE] = std::make_unique<Commands::MouseMove>();
	_eventCommand[CMD_MOUSE_SCROLL] = std::make_unique<Commands::MouseScroll>();
	_eventCommand[GLFW_KEY_ESCAPE] = std::make_unique<Commands::CloseWindow>();
	// Repeat Key
	_continuousCommand[GLFW_KEY_W] = std::make_unique<Commands::CameraForward>();
	_continuousCommand[GLFW_KEY_S] = std::make_unique<Commands::CameraBackward>();
	_continuousCommand[GLFW_KEY_A] = std::make_unique<Commands::CameraLeft>();
	_continuousCommand[GLFW_KEY_D] = std::make_unique<Commands::CameraRight>();
}

InputHandler::~InputHandler() {};

void InputHandler::executeID(Application* app, int id)
{
	auto iterator = _eventCommand.find(id);
	if (iterator == _eventCommand.end())
		return;
	iterator->second->execute(app);
}

void InputHandler::handleKeysCallback(Application* app, int key)
{
	executeID(app, key);
};

void InputHandler::handleMouseMove(Application* app)
{
	executeID(app, CMD_MOUSE_MOVE);
}

void InputHandler::handleMouseScroll(Application* app)
{
	executeID(app, CMD_MOUSE_SCROLL);
}

void InputHandler::handleKeys(Application* app)
{
	InputContext& ctx = app->inputContext();

	for (auto& [key, command] : _continuousCommand)
	{
		if (ctx.keys[key])
			command->execute(app);
	}
}