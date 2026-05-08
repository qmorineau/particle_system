#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include <memory>

#include "ParticlesGPU.hpp"
#include "EmitterGPU.hpp"
#include "GravityGPU.hpp"

class ParticleSystem
{
	public:
		ParticleSystem(unsigned int particles);
		~ParticleSystem();

		ParticlesGPU&		particles() {return *_particlesGPU;};
		const ParticlesGPU&	particles() const {return *_particlesGPU;};
		EmitterGPU&			emitter() {return *_emitterGPU;};
		const EmitterGPU&	emitter() const {return *_emitterGPU;};
		GravityGPU&			gravity() {return *_gravityGPU;};
		const GravityGPU&	gravity() const {return *_gravityGPU;};
	private:
		std::unique_ptr<ParticlesGPU>	_particlesGPU;
		std::unique_ptr<EmitterGPU>		_emitterGPU;
		std::unique_ptr<GravityGPU>		_gravityGPU;
};

#endif