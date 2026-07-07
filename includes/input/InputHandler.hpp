#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <memory>
#include <array>
#include <unordered_map>

class ICommand;
class Application;


class InputHandler
{
	public:
		enum class Scancode
		{
			KEY_ESC = 1,
			KEY_TAB = 15,
			KEY_G = 34,
			KEY_E = 18,
			KEY_1 = 2,
			KEY_2 = 3,
			KEY_R = 19,
			KEY_C = 46,
			KEY_F1 = 59,
			KEY_F2 = 60,
			KEY_W = 17,
			KEY_A = 30,
			KEY_S = 31,
			KEY_D = 32,
			KEY_LEFT = 105,
			KEY_RIGHT = 106,
			KEY_UP = 103,
			KEY_DOWN = 108,
		};
		enum CommandID
		{
			CMD_MOUSE_MOVE = 9,
			CMD_MOUSE_SCROLL = 10,
		};
		InputHandler();
		~InputHandler();
		
		void onKeyPressed(Application* app, int key);
		void onMouseEvent(Application* app, int key);
		void updateHeldKey(Application* app);

	private:
		struct InputKey
		{
			int key;
			int mod;
			bool operator==(const InputKey& k) const
			{
				return (k.key == key && k.mod == mod);
			};
		};
		struct InputKeyHash // to put in the hashtable 
		{
			size_t operator()(const InputKey& k) const
			{
				return k.key | (k.mod << 16);  // bits 0-15 = key, bits 16-31 = mod
			}    
		};

		struct InputBindings
		{
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> onPressed;
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> whileHeld;
			std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash> mouse;
		};

		InputBindings	_commands;

		bool executeCommand(Application * app, std::unordered_map<InputKey, std::unique_ptr<ICommand>, InputKeyHash>& map, InputKey key);
};

 #endif