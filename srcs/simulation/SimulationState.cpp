#include "SimulationState.hpp"

SimulationState::SimulationState() {};

SimulationState::~SimulationState() {};

void SimulationState::accelerateTimeSpeed()
{
	if (_timeSpeed < 1.f)
	{
		_timeSpeed += 0.01;
		if (_timeSpeed > 1.f)
			_timeSpeed = 1.f;
	}
};

void SimulationState::slowTimeSpeed()
{
	if (_timeSpeed > 0.f)
	{
		_timeSpeed -= 0.01;
		if (_timeSpeed < 0.f)
			_timeSpeed = 0.f;
	}
};

void SimulationState::changeColorMode()
{
	_colorMode = static_cast<ColorMode>((static_cast<int>(_colorMode) + 1) % static_cast<int>(ColorMode::COUNT));
};