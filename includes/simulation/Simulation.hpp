#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Shader.hpp"

class SimulationState;
class ParticleSystem;

class Simulation
{
	public:
		enum class Shape
		{
			Cube,
			Sphere
		};
		Simulation();
		~Simulation();

		void simulate(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const;
		void setShape(const SimulationState& state, const ParticleSystem& ps, Shape shape) const;
	private:
		Shader	_update;
		Shader	_shape;
		Shader	_emitter;
		Shader	_gravity;

		void setEmitter(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const;
		void setGravity(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const;
		void setUpdate(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const;
};

#endif