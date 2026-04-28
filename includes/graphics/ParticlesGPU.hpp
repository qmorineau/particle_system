#ifndef PARTICLESGPU_HPP
#define PARTICLESGPU_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class ParticlesGPU
{
	public:
		struct Particle
		{
			vec3 position;
			vec3 velocity;
			vec3 color;
		};
		ParticlesGPU(unsigned long);
		~ParticlesGPU();

		void draw(Shader&) const;

	private:
		unsigned long   _particles;
		GLuint          _vao = 0;
		GLuint          _ssbo = 0;

		void createVAO();
		void createSSBO();
};

#endif