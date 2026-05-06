#include "EmitterGPU.hpp"

EmitterGPU::EmitterGPU()
{
    createSSBO();
}
 
EmitterGPU::~EmitterGPU() {};

void EmitterGPU::createSSBO()
{
    glGenBuffers(1, &_ssbo);
	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
	GLsizei stride = sizeof(Emitter);
	glBufferData(GL_SHADER_STORAGE_BUFFER, stride, NULL, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, _ssbo);
}

void EmitterGPU::compute(const Shader& shader) const
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, _ssbo);
	
	shader.use();
	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); // be sure that compute shader have finish writing before continue
}