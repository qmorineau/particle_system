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
	// Use shader
    _render.use();

	// Draw
	scene->particles().bindVAO();
	glDrawArrays(GL_POINTS, 0, scene->getParticles());
}

