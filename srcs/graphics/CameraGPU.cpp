#include "CameraGPU.hpp"
#include "Camera.hpp"

static_assert(offsetof(CameraGPU::CameraUBO, mouseNDC) == 144, "bad padding");
static_assert(sizeof(CameraGPU::CameraUBO) == 160, "bad size");

CameraGPU::CameraGPU()
{
	createCameraUBO();
}

CameraGPU::~CameraGPU() {}

void CameraGPU::createCameraUBO()
{
	glGenBuffers(1, &_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUBO), nullptr, GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, _ubo);
}

void CameraGPU::updateCameraUBO()
{
	glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraUBO), &_data);
}

void CameraGPU::setData(const Camera& camera, const vec2 mouseNDC)
{
	_data.projection = mat4::perspective(math::radians(camera.getZoom()), camera.getAspectRatio(), camera.getNear(), camera.getFar());
	_data.view = camera.getViewMatrix();
	_data.viewPos = camera.getPosition();
	_data.mouseNDC = mouseNDC;
	_data.nearPlan = camera.getNear();
	_data.farPlan = camera.getFar();
}