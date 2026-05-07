#ifndef SSBO_HPP
#define SSBO_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class SSBO
{
	public:
		SSBO(GLuint binding, size_t size) : _binding(binding), _size(size)
		{
			glGenBuffers(1, &_id);
			allocate(_size);
		};
		~SSBO()
		{
			glDeleteBuffers(1, &_id);
		}
		void allocate(size_t size)
		{
			_size = size;
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
			glBufferData(GL_SHADER_STORAGE_BUFFER, _size, nullptr, GL_DYNAMIC_COPY);
		};
		void bind() const
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, _binding, _id);
		};
	private:
		GLuint _id;
		GLuint _binding;
		size_t _size;
};

template <typename T>

class TypedSSBO : public SSBO
{
	public:
		TypedSSBO(size_t count) : SSBO(T::binding, sizeof(T) * count) {};
};

#endif