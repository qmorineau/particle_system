#include "ParticlesGPU.hpp"

ParticlesGPU::ParticlesGPU(unsigned long p) : _particles(p)
{
    createSSBO();
    createVAO();
}
 
void ParticlesGPU::createVAO()
{
    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _ssbo); // make vao and ssbo the same buffer

	GLsizei stride = sizeof(Particle);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Particle, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Particle, color));
	glEnableVertexAttribArray(2);
}

void ParticlesGPU::createSSBO()
{
    glGenBuffers(1, &_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
	
	GLsizei stride = sizeof(Particle);

	glBufferData(GL_SHADER_STORAGE_BUFFER, _particles * stride, NULL, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _ssbo);
}