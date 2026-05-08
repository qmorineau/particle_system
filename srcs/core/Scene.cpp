#include "Scene.hpp"
#include "ParticlesGPU.hpp"
#include "EmitterGPU.hpp"
#include "GravityGPU.hpp"
#include "Window.hpp"

Scene::Scene(unsigned int particles) :
	_particleSystem(particles),
	_camera(SCR_WIDTH, SCR_HEIGHT)
{}

Scene::~Scene() {}

void Scene::update(float deltaTime, const vec2& mouseNDC)
{
	(void) deltaTime;
	_cameraGPU.setData(_camera, mouseNDC);
	_cameraGPU.updateCameraUBO();
};
