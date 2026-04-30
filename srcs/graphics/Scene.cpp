#include "Scene.hpp"
#include "ParticlesGPU.hpp"
#include "Window.hpp"

Scene::Scene(unsigned int particles) :
	_particlesGPU(nullptr),
	_particles(particles),
	_camera(SCR_WIDTH, SCR_HEIGHT)
{
	_particlesGPU = new ParticlesGPU(_particles);
}

Scene::~Scene()
{
	if (_particlesGPU)
		delete _particlesGPU;
}

void Scene::update(float deltaTime)
{
	(void) deltaTime;
};
