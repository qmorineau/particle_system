#include "Simulation.hpp"
#include "SimulationState.hpp"
#include "ParticleSystem.hpp"

Simulation::Simulation() :
	_update("assets/shaders/compute/update.comp"),
	_shape("assets/shaders/compute/shape.comp"),
	_emitter("assets/shaders/compute/emitter.comp"),
	_gravity("assets/shaders/compute/gravity.comp")
{

};

Simulation::~Simulation() {};

void Simulation::simulate(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const
{	
	setEmitter(state, ps, deltaTime);
	setGravity(state, ps, deltaTime);
	setUpdate(state, ps, deltaTime);
};

void Simulation::setEmitter(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const
{
	_emitter.use();
	_emitter.setFloat("delta_time", deltaTime);
	_emitter.setFloat("time_speed", state.timeSpeed());
	_emitter.setBool("track_emitter", state.mouseTarget() == SimulationState::MouseTarget::Emitter ? true : false);
	ps.emitter().compute(_emitter);
};

void Simulation::setGravity(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const
{
	_gravity.use();
	_gravity.setFloat("delta_time", deltaTime);
	_gravity.setFloat("time_speed", state.timeSpeed());
	_gravity.setBool("track_gravity", state.mouseTarget() == SimulationState::MouseTarget::Gravity ? true : false);
	ps.gravity().compute(_gravity);
};

void Simulation::setUpdate(const SimulationState& state, const ParticleSystem& ps, const float deltaTime) const
{
	_update.use();
	_update.setFloat("life_span", state.lifespan());
	_update.setFloat("delta_time", deltaTime);
	_update.setInt("particles_nbr", state.count());
	_update.setInt("max_particles_nbr", state.maxParticles());
	_update.setBool("emitter_on", state.isEmitter());
	_update.setBool("gravity_on", state.isGravity());
	_update.setFloat("time_speed", state.timeSpeed());
	ps.particles().compute(_update);
};

void Simulation::setShape(const SimulationState& state, const ParticleSystem& ps, Shape shape) const
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
	_shape.setInt("particles_nbr", state.count());
	_shape.setFloat("life_span", state.lifespan());
	ps.particles().compute(_shape);
};
