#include "Scene.hpp"
#include "ParticlesGPU.hpp"
#include "EmitterGPU.hpp"
#include "Window.hpp"

Scene::Scene(unsigned int particles) :
	_particlesGPU(nullptr),
	_emitterGPU(nullptr),
	_particles(particles),
	_camera(SCR_WIDTH, SCR_HEIGHT)
{
	_particlesGPU = new ParticlesGPU(_particles);
	_emitterGPU = new EmitterGPU();
}

Scene::~Scene()
{
	if (_particlesGPU)
		delete _particlesGPU;
	if (_emitterGPU)
		delete _emitterGPU;
}

void Scene::update(float deltaTime, const vec2& mouseNDC)
{
	(void) deltaTime;
	_cameraGPU.setData(_camera, mouseNDC);
	_cameraGPU.updateCameraUBO();
	if (_newEmitter)
		_newEmitter = false;
};

void Scene::accelerateTimeSpeed()
{
	if (_timeSpeed < 1.f)
	{
		_timeSpeed += 0.01;
		if (_timeSpeed > 1.f)
			_timeSpeed = 1.f;
	}
};

void Scene::slowTimeSpeed()
{
	if (_timeSpeed > 0.f)
	{
		_timeSpeed -= 0.01;
		if (_timeSpeed < 0.f)
			_timeSpeed = 0.f;
	}
};