#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class ParticlesGPU;

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void beginFrame();
		void draw(const ParticlesGPU& p);
	private:
		Shader	_render;
};

#endif