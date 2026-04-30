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
		InputHandler();
		~InputHandler();
		
		void handleKeysCallback(Application* app, int key);
		void handleMouseScroll(Application* app);
		void handleMouseMove(Application* app);
		void handleKeys(Application* app);

	private:
		enum CommandID
		{
			CMD_MOUSE_MOVE = 10000,
			CMD_MOUSE_SCROLL = 10001
		};
		std::unordered_map<int, std::unique_ptr<ICommand>> _eventCommand;
		std::unordered_map<int, std::unique_ptr<ICommand>> _continuousCommand;
		void executeID(Application* app, int id);
};

 #endif