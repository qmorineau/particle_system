#include "Renderer.hpp"
#include "Matrix4.hpp"
#include "Math.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "ParticlesGPU.hpp"

Renderer::Renderer() :
	_render("assets/shaders/shaderRender.vs", "assets/shaders/shaderRender.fs"),
	_update("assets/shaders/shaderUpdate.cs")
{};

Renderer::~Renderer() {};

void Renderer::beginFrame()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::draw(Scene* scene)
{
	// Use shader
    _render.use();

	// Camera
	Camera& camera = scene->camera();
    mat4 projection = mat4::perspective(math::radians(camera.getZoom()), camera.getAspectRatio(), 0.001f, 100.0f);
    _render.setMat4("projection", projection);
    _render.setMat4("view", camera.getViewMatrix());
	_render.setVec3("viewPos", vec3(camera.getPosition()));

	// Model
	const vec3 angle = scene->getRotAngle();
	mat4 model = mat4::rotateX(angle.x)
		.mul_mat(mat4::rotateY(angle.y))
		.mul_mat(mat4::rotateZ(angle.z));
    _render.setMat4("model", model);

	// Compute Shader
	const ParticlesGPU& particles = scene->particles();
	particles.compute(_update);

	// Draw
	particles.bindVAO();
	glDrawArrays(GL_POINTS, 0, scene->getParticles());
}

