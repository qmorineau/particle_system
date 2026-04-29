#include "ParticlesGPU.hpp"

ParticlesGPU::ParticlesGPU(unsigned long p) : _particles(p)
{
    createSSBO();
    createVAO();
}
 
ParticlesGPU::~ParticlesGPU() {};

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

void ParticlesGPU::compute(Shader& shader) const
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, _ssbo);
	
	shader.use();
	
	// 1 thread per particule
	GLuint num_group_x = std::ceil(static_cast<float>(_particles) / 256.0f);
	// set at 1 because it's particle[], if particle[][] use y, and if particle[][][] use z
	GLuint num_group_y = 1;
	GLuint num_group_z = 1;
	glDispatchCompute(num_group_x, num_group_y, num_group_z);
	
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); // be sure that compute shader have finish writing before continue
}

void ParticlesGPU::bindVAO() const
{
    glBindVertexArray(_vao);
}