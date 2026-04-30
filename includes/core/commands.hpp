#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ICommand.hpp"

namespace Commands
{
	class CloseWindow : public ICommand
	{
		void execute(Application* app) const override;
	};

	class MouseMove : public ICommand
	{
		void execute(Application* app) const override;
	};

	class MouseScroll : public ICommand
	{
		void execute(Application* app) const override;
	};

	class CameraForward : public ICommand
	{
		void execute(Application* app) const override;
	};

	class CameraBackward : public ICommand
	{
		void execute(Application* app) const override;
	};

	class CameraLeft : public ICommand
	{
		void execute(Application* app) const override;
	};

	class CameraRight : public ICommand
	{
		void execute(Application* app) const override;
	};
};

#endif