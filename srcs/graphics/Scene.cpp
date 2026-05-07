#include "Scene.hpp"
#include "ParticlesGPU.hpp"
#include "EmitterGPU.hpp"
#include "GravityGPU.hpp"
#include "Window.hpp"

Scene::Scene(unsigned int particles) :
	_particles(particles),
	_camera(SCR_WIDTH, SCR_HEIGHT)
{
	_particlesGPU = std::make_unique<ParticlesGPU>(_particles);
	_emitterGPU = std::make_unique<EmitterGPU>();
	_gravityGPU = std::make_unique<GravityGPU>();
}

Scene::~Scene() {}

void Scene::update(float deltaTime, const vec2& mouseNDC)
{
	(void) deltaTime;
	_cameraGPU.setData(_camera, mouseNDC);
	_cameraGPU.updateCameraUBO();
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

void Scene::changeColorMode()
{
	_colorMode = static_cast<ColorMode>((_colorMode + 1) % COUNT);
};