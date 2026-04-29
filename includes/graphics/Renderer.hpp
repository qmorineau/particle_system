#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class Scene;

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void beginFrame();
		void draw(Scene* scene, float deltaTime);
	private:
		Shader	_render;
		Shader	_update;
		Shader	_flocking;
};

#endif