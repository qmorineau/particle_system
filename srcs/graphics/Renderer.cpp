#include "Renderer.hpp"
#include "ParticleSystem.hpp"
#include "SimulationState.hpp"
#include "TextureLoader.hpp"

Renderer::Renderer() :
	_render("assets/shaders/render/particle.vert", "assets/shaders/render/particle.frag")
{
	try
	{
		_smokeTexture = TextureLoader::load("assets/texture/smoke.png");
		_magicTexture = TextureLoader::load("assets/texture/magic.png");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
};

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
	_render.setInt("particles_mode", static_cast<int>(state.particlesMode()));
	// texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _smokeTexture);
	_render.setInt("textures[0]", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _magicTexture);
	_render.setInt("textures[1]", 1);
 
	// Draw
	ps.particles().bindVAO();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
 	// glBlendFunc(GL_ONE, GL_ONE);

	glDrawArrays(GL_POINTS, 0, state.count());
	glDepthMask(GL_TRUE);
}

