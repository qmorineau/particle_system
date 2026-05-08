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
		enum CommandID
		{
			CMD_MOUSE_MOVE = 9,
			CMD_MOUSE_SCROLL = 10,
		};
		InputHandler();
		~InputHandler();
		
		void handleKeysCallback(Application* app, int key);
		void handleMouseCallback(Application* app, int key);
		void handleKeys(Application* app);

	private:
		std::unordered_map<int, std::unique_ptr<ICommand>> _eventKeyCommand;
		std::unordered_map<int, std::unique_ptr<ICommand>> _eventMouseCommand;
		std::unordered_map<int, std::unique_ptr<ICommand>> _continuousCommand;
};

 #endif