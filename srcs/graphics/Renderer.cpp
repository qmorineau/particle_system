#include "Renderer.hpp"
#include "Matrix4.hpp"
#include "Math.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "ParticlesGPU.hpp"

Renderer::Renderer() :
	_render("assets/shaders/render/particle.vert", "assets/shaders/render/particle.frag")
{};

Renderer::~Renderer() {};

void Renderer::beginFrame()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(Scene* scene)
{
	// const ParticlesGPU& particles = scene->particles();

	// _update.use();
	// _update.setBool("gravity_on", false);
	// _update.setVec3("gravity_pos", vec3(0, 0, 0));
	// _update.setFloat("delta_time", deltaTime);
	// _update.setInt("particles_nbr", scene->getParticles());
	// particles.compute(_update);
	
	// Compute Shader
	// _flocking.use();
	// _flocking.setInt("particles_nbr", scene->getParticles());
	// _flocking.setFloat("delta_time", deltaTime);
	// _flocking.setFloat("sphereRadius", 20.0f); // taille de la sphère
	// particles.compute(_flocking);

	// Use shader
    _render.use();

	// Camera
	Camera& camera = scene->camera();
    mat4 projection = mat4::perspective(math::radians(camera.getZoom()), camera.getAspectRatio(), 0.001f, 100.0f);
    _render.setMat4("projection", projection);
    _render.setMat4("view", camera.getViewMatrix());
	_render.setVec3("viewPos", vec3(camera.getPosition()));

	// Draw
	scene->particles().bindVAO();
	glDrawArrays(GL_POINTS, 0, scene->getParticles());
}

