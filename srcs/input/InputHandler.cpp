#include "InputHandler.hpp"
#include "commands.hpp"
#include "Application.hpp"

InputHandler::InputHandler()
{
	using IK = InputKey;
	using SC = Scancode;
	// Mouse Button
	auto& mouseMap = _commands.mouse;
	mouseMap[IK{GLFW_MOUSE_BUTTON_LEFT, 0}] = std::make_unique<Commands::DisableMouse>();
	mouseMap[IK{GLFW_MOUSE_BUTTON_LEFT, GLFW_MOD_ALT}] = std::make_unique<Commands::MoveEmitter>();
	mouseMap[IK{GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOD_ALT}] = std::make_unique<Commands::MoveGravity>();
	mouseMap[IK{CMD_MOUSE_MOVE, 0}] = std::make_unique<Commands::MouseMove>();
	mouseMap[IK{CMD_MOUSE_SCROLL, 0}] = std::make_unique<Commands::MouseScroll>();

	// Key Press
	auto& onPressedMap = _commands.onPressed;
	onPressedMap[IK{_scancodes.get(SC::KEY_ESC), 0}] = std::make_unique<Commands::CloseWindow>();
	onPressedMap[IK{_scancodes.get(SC::KEY_TAB), 0}] = std::make_unique<Commands::EnableMouse>();
	onPressedMap[IK{_scancodes.get(SC::KEY_G), 0}] = std::make_unique<Commands::ToggleGravity>();
	onPressedMap[IK{_scancodes.get(SC::KEY_E), 0}] = std::make_unique<Commands::ToggleEmitter>();
	onPressedMap[IK{_scancodes.get(SC::KEY_1), 0}] = std::make_unique<Commands::SetCubeShape>();
	onPressedMap[IK{_scancodes.get(SC::KEY_2), 0}] = std::make_unique<Commands::SetSphereShape>();
	onPressedMap[IK{_scancodes.get(SC::KEY_R), 0}] = std::make_unique<Commands::CameraReset>();
	onPressedMap[IK{_scancodes.get(SC::KEY_C), 0}] = std::make_unique<Commands::ChangeColorMode>();
	onPressedMap[IK{_scancodes.get(SC::KEY_F1), 0}] = std::make_unique<Commands::DefaultMode>();
	onPressedMap[IK{_scancodes.get(SC::KEY_F2), 0}] = std::make_unique<Commands::SmokeMode>();

	// Repeat Key
	auto& whileHeldMap = _commands.whileHeld;
	whileHeldMap[IK{_scancodes.get(SC::KEY_W), 0}] = std::make_unique<Commands::CameraForward>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_S), 0}] = std::make_unique<Commands::CameraBackward>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_A), 0}] = std::make_unique<Commands::CameraLeft>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_D), 0}] = std::make_unique<Commands::CameraRight>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_LEFT), 0}] = std::make_unique<Commands::SlowTime>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_RIGHT), 0}] = std::make_unique<Commands::AccelerateTime>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_UP), 0}] = std::make_unique<Commands::AddParticles>();
	whileHeldMap[IK{_scancodes.get(SC::KEY_DOWN), 0}] = std::make_unique<Commands::RemoveParticles>();
}

InputHandler::~InputHandler() {};

void InputHandler::onKeyPressed(Application* app, int key)
{
	InputKey inputKey = {key, app->inputContext().getMods()};
	executeCommand(app, _commands.onPressed, inputKey);
};

void InputHandler::onMouseEvent(Application* app, int key)
{
	InputKey inputKey = {key, app->inputContext().getMods()};
	executeCommand(app, _commands.mouse, inputKey);
}

void InputHandler::updateHeldKey(Application* app)
{
	InputContext ctx = app->inputContext();

	for (const auto& key : ctx.activeKeys())
	{
		InputKey inputKey = {key, app->inputContext().getMods()};
		executeCommand(app, _commands.whileHeld, inputKey);
	}
}

bool InputHandler::executeCommand(Application * app, std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash>& map, InputKey key)
{
	const auto& it = map.find(key);
	if (it != map.end())
	{
		it->second->execute(app);
		return true;
	}
	else
		return false;
};