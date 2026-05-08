#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(unsigned int particles)
{
	_particlesGPU = std::make_unique<ParticlesGPU>(particles);
	_emitterGPU = std::make_unique<EmitterGPU>();
	_gravityGPU = std::make_unique<GravityGPU>();
}

ParticleSystem::~ParticleSystem() {}