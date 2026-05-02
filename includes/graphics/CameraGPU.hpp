#ifndef CAMERAGPU_HPP
#define CAMERAGPU_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Types.hpp"
#include "Matrix4.hpp"

class Camera;

class CameraGPU
{
	public:
		struct CameraUBO
		{
			mat4 projection;
			mat4 view;
			vec3 viewPos;
			float pad0; // aligned to 16 bytes
			vec2 mouseNDC; // Normalize Device Coordinate
			float nearPlan;
			float farPlan;
		};

		CameraGPU();
		~CameraGPU();
		
		void updateCameraUBO();
		void setData(const Camera& camera, const vec2 mouseNDC);
	private:
		GLuint		_ubo;
		CameraUBO	_data;
		
		void createCameraUBO();
};

#endif