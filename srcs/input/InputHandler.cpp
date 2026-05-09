#include "InputHandler.hpp"
#include "commands.hpp"
#include "Application.hpp"

InputHandler::InputHandler()
{
	// Key Press
	_eventMouseCommand[GLFW_MOUSE_BUTTON_LEFT] = std::make_unique<Commands::DisableMouse>();
	_eventMouseCommand[CMD_MOUSE_MOVE] = std::make_unique<Commands::MouseMove>();
	_eventMouseCommand[CMD_MOUSE_SCROLL] = std::make_unique<Commands::MouseScroll>();
	_eventKeyCommand[GLFW_KEY_ESCAPE] = std::make_unique<Commands::CloseWindow>();
	_eventKeyCommand[GLFW_KEY_TAB] = std::make_unique<Commands::EnableMouse>();
	_eventKeyCommand[GLFW_KEY_G] = std::make_unique<Commands::ToggleGravity>();
	_eventKeyCommand[GLFW_KEY_E] = std::make_unique<Commands::ToggleEmitter>();
	_eventKeyCommand[GLFW_KEY_1] = std::make_unique<Commands::SetCubeShape>();
	_eventKeyCommand[GLFW_KEY_2] = std::make_unique<Commands::SetSphereShape>();
	_eventKeyCommand[GLFW_KEY_0] = std::make_unique<Commands::MoveEmitter>();
	_eventKeyCommand[GLFW_KEY_9] = std::make_unique<Commands::MoveGravity>();
	_eventKeyCommand[GLFW_KEY_R] = std::make_unique<Commands::CameraReset>();
	_eventKeyCommand[GLFW_KEY_C] = std::make_unique<Commands::ChangeColorMode>();
	// Repeat Key
	_continuousCommand[GLFW_KEY_W] = std::make_unique<Commands::CameraForward>();
	_continuousCommand[GLFW_KEY_S] = std::make_unique<Commands::CameraBackward>();
	_continuousCommand[GLFW_KEY_A] = std::make_unique<Commands::CameraLeft>();
	_continuousCommand[GLFW_KEY_D] = std::make_unique<Commands::CameraRight>();
	_continuousCommand[GLFW_KEY_LEFT] = std::make_unique<Commands::SlowTime>();
	_continuousCommand[GLFW_KEY_RIGHT] = std::make_unique<Commands::AccelerateTime>();
	_continuousCommand[GLFW_KEY_UP] = std::make_unique<Commands::AddParticles>();
	_continuousCommand[GLFW_KEY_DOWN] = std::make_unique<Commands::RemoveParticles>();
}

InputHandler::~InputHandler() {};

void InputHandler::handleKeysCallback(Application* app, int key)
{
	auto iterator = _eventKeyCommand.find(key);
	if (iterator == _eventKeyCommand.end())
		return;
	iterator->second->execute(app);
};

void InputHandler::handleMouseCallback(Application* app, int key)
{
	auto iterator = _eventMouseCommand.find(key);
	if (iterator == _eventMouseCommand.end())
		return;
	iterator->second->execute(app);
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