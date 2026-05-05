#include "Simulation.hpp"
#include "ParticlesGPU.hpp"
#include "Scene.hpp"

Simulation::Simulation() :
	_update("assets/shaders/compute/update.comp"),
	_shape("assets/shaders/compute/shape.comp")
{

};

Simulation::~Simulation() {};

void Simulation::simulate(const Scene& scene, const vec2& mouseNDC, float deltaTime) const
{
	int particlesNbr = scene.getParticles();
	ParticlesGPU& particles = scene.particles();

	_update.use();
	_update.setFloat("life_span", 5.f);
	_update.setFloat("delta_time", deltaTime);
	_update.setInt("particles_nbr", particlesNbr);
	_update.setBool("emitter_on", scene.getEmitter());
	_update.setBool("gravity_on", scene.getGravity());
	_update.setVec2("mouse_pos", mouseNDC);
	_update.setFloat("time_speed", scene.getTimeSpeed());
	particles.compute(_update);
};

void Simulation::setShape(const Scene& scene, Shape shape) const
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
	_shape.setInt("particles_nbr", scene.getParticles());
	scene.particles().compute(_shape);
};
