#include "Simulation.hpp"
#include "ParticlesGPU.hpp"
#include "EmitterGPU.hpp"
#include "Scene.hpp"

Simulation::Simulation() :
	_update("assets/shaders/compute/update.comp"),
	_shape("assets/shaders/compute/shape.comp"),
	_emitter("assets/shaders/compute/emitter.comp")
{

};

Simulation::~Simulation() {};

void Simulation::simulate(const Scene& scene, const vec2& mouseNDC, float deltaTime) const
{	
	_emitter.use();
	_emitter.setVec2("mouse_pos", mouseNDC);
	_emitter.setFloat("delta_time", deltaTime);
	_emitter.setFloat("time_speed", scene.getTimeSpeed());
	_emitter.setBool("track_emitter", scene.getTracking() == Scene::PosTracked::Emitter ? true : false);
	scene.emitter().compute(_emitter);
	
	_update.use();
	_update.setFloat("life_span", scene.getLifespan());
	_update.setFloat("delta_time", deltaTime);
	_update.setInt("particles_nbr", scene.getParticles());
	_update.setBool("emitter_on", scene.getEmitter());
	_update.setBool("gravity_on", scene.getGravity());
	_update.setBool("track_gravity", scene.getTracking() == Scene::PosTracked::Gravity ? true : false);
	_update.setVec2("mouse_pos", mouseNDC);
	_update.setFloat("time_speed", scene.getTimeSpeed());
	_update.setInt("color_mode", scene.getColorMode());
	scene.particles().compute(_update);
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
	_shape.setFloat("life_span", scene.getLifespan());
	scene.particles().compute(_shape);
};
