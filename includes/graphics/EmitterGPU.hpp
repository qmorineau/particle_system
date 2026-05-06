#ifndef EMITTERGPU_HPP
#define EMITTERGPU_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class EmitterGPU
{
	public:
		struct Emitter
		{
			vec4 	position;
			vec4 	velocity;
		}; // need to be 16 bytes aligned for glsl 430
		EmitterGPU();
		~EmitterGPU();

		void compute(const Shader&) const;

	private:
		GLuint          _ssbo = 0;

		void createSSBO();
};

#endif