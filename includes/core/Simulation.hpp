#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Shader.hpp"

class ParticlesGPU;

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

		void simulate(const ParticlesGPU& particles, int particlesNbr, float deltaTime) const;
		void setShape(const ParticlesGPU& particles, int particlesNbr, Shape shape) const;
	private:
		Shader	_update;
		Shader	_shape;
		// Shader	_gravity;
};

#endif