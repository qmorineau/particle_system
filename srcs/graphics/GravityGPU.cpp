#include "GravityGPU.hpp"

GravityGPU::GravityGPU()
	: _ssbo(1)
{};

GravityGPU::~GravityGPU() {};

void GravityGPU::compute(const Shader& shader) const
{
	_ssbo.bind();
	shader.use();
	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); // be sure that compute shader have finish writing before continue
}