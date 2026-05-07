#ifndef GRAVITYGPU_HPP
#define GRAVITYGPU_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SSBO.hpp"
#include "dataTypes.hpp"
#include "Shader.hpp"

class GravityGPU
{
	public:
		GravityGPU();
		~GravityGPU();

		void compute(const Shader&) const;
	private:
		TypedSSBO<Gravity>	_ssbo;
};

#endif