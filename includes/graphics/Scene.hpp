#ifndef SCENE_HPP
#define SCENE_HPP

#include "Types.hpp"
#include "Camera.hpp"
#include "CameraGPU.hpp"

class ParticlesGPU;

class Scene
{
	public:
		Scene(unsigned int);
		~Scene();

		void update(float deltaTime, const vec2& mouseNDC);

		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			toggleEmitter() {_isEmitter = !_isEmitter;};

		// getter
		Camera&			camera() {return _camera;};
		const Camera&	camera() const {return _camera;};
		ParticlesGPU&	particles() const {return *_particlesGPU;};
		int				getParticles() const {return _particles;};
		bool			getGravity() const {return _isGravity;};
		bool			getEmitter() const {return _isEmitter;};
	private:
		ParticlesGPU*	_particlesGPU;
		CameraGPU		_cameraGPU;
		unsigned int	_particles;
		Camera			_camera;
		bool			_isGravity = false;
		bool			_isEmitter = false;

		void applyRotation(float deltaTime);
};

#endif