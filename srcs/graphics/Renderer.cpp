#include "Renderer.hpp"
#include "ParticleSystem.hpp"
#include "SimulationState.hpp"

Renderer::Renderer() :
	_render("assets/shaders/render/particle.vert", "assets/shaders/render/particle.frag")
{};

Renderer::~Renderer() {};

void Renderer::beginFrame()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(const SimulationState& state, const ParticleSystem& ps)
{
	// Use shader
    _render.use();
	_render.setInt("color_mode", static_cast<int>(state.colorMode()));
	_render.setBool("track_mouse", state.mouseTarget() == SimulationState::MouseTarget::Camera ? false : true);
	_render.setFloat("life_span", state.lifespan());

	// Draw
	ps.particles().bindVAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDrawArrays(GL_POINTS, 0, state.count());
}

