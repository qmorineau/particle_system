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
			vec4 position;
			vec4 velocity;
			vec4 color;
		};
		ParticlesGPU(unsigned long);
		~ParticlesGPU();

		void compute(const Shader&) const;
		void bindVAO() const;

	private:
		unsigned long   _particles;
		GLuint          _vao = 0;
		GLuint          _ssbo = 0;

		void createVAO();
		void createSSBO();
};

#endif