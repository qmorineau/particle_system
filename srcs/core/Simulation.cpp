#include "Simulation.hpp"
#include "ParticlesGPU.hpp"

Simulation::Simulation() :
	_update("assets/shaders/compute/update.comp"),
	_shape("assets/shaders/compute/shape.comp")
{

};

Simulation::~Simulation() {};

void Simulation::simulate(const ParticlesGPU& particles, int particlesNbr, float deltaTime) const
{
	_update.use();
	_update.setFloat("delta_time", deltaTime);
	_update.setInt("particles_nbr", particlesNbr);
	particles.compute(_update);
};

void Simulation::setShape(const ParticlesGPU& particles, int particlesNbr, Shape shape) const
{
	_shape.use();
	switch (shape)
	{
		case Shape::Cube:
			_shape.setBool("is_cube", true);
			_shape.setBool("is_sphere", false);
			break;
		case Shape::Sphere:
			_shape.setBool("is_cube", false);
			_shape.setBool("is_sphere", true);
			break;
	}
	_shape.setInt("particles_nbr", particlesNbr);
	particles.compute(_shape);
};
