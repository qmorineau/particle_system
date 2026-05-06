#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Shader.hpp"

class Scene;
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

		void simulate(const Scene& scene, const vec2& mouse, float deltaTime) const;
		void setShape(const Scene& scene, Shape shape) const;
	private:
		Shader	_update;
		Shader	_shape;
		Shader	_emitter;
};

#endif