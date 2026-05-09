#include "SimulationState.hpp"

SimulationState::SimulationState(unsigned int particles)
	: _particlesMax(particles), _particlesNbr(particles)
{};

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

void SimulationState::addParticles()
{
	long tmp = _particlesNbr + _particlesIncr;
	if (tmp > _particlesMax)
		_particlesNbr = _particlesMax;
	else
		_particlesNbr = tmp;
};

void SimulationState::removeParticles()
{
	long tmp = _particlesNbr - _particlesIncr;
	if (tmp < _particlesIncr)
		_particlesNbr = _particlesIncr;
	else
		_particlesNbr = tmp;
};