#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class ParticleSystem;
class SimulationState;

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void beginFrame();
		void draw(const SimulationState& state, const ParticleSystem& p);
	private:
		Shader	_render;
};

#endif