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

		void simulate(const Scene& scene, const float deltaTime) const;
		void setShape(const Scene& scene, Shape shape) const;
	private:
		Shader	_update;
		Shader	_shape;
		Shader	_emitter;
		Shader	_gravity;

		void setEmitter(const Scene& scene, const float deltaTime) const;
		void setGravity(const Scene& scene, const float deltaTime) const;
		void setUpdate(const Scene& scene, const float deltaTime) const;
};

#endif