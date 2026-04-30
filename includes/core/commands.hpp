#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "ICommand.hpp"

namespace Commands
{
	// Window
	class CloseWindow : public ICommand
	{
		void execute(Application* app) const override;
	};
	// Mouse
	class MouseMove : public ICommand
	{
		void execute(Application* app) const override;
	};

	class MouseScroll : public ICommand
	{
		void execute(Application* app) const override;
	};

	class ToggleMouse : public ICommand
	{
		void execute(Application* app) const override;
	};
	// Camera
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
	// Shape
	class SetCubeShape : public ICommand
	{
		void execute(Application* app) const override;
	};
	class SetSphereShape : public ICommand
	{
		void execute(Application* app) const override;
	};
	// Simulation
	class ToggleGravity : public ICommand
	{
		void execute(Application* app) const override;
	};
};

#endif