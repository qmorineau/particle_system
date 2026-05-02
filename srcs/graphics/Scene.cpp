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

void Scene::update(float deltaTime, const vec2& mouseNDC)
{
	(void) deltaTime;
	_cameraGPU.setData(_camera, mouseNDC);
	_cameraGPU.updateCameraUBO();
};
