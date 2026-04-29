#ifndef SCENE_HPP
#define SCENE_HPP

#include "Types.hpp"
#include "Camera.hpp"

class ParticlesGPU;

class Scene
{
	public:
		Scene(unsigned int);
		~Scene();

		void update(float deltaTime);

		// getter
		Camera&			camera() {return _camera;};
		ParticlesGPU&	particles() {return *_particlesGPU;};
		const vec3&		getRotAngle() const {return _rotAngle;};
		int				getParticles() const {return _particles;};
		// setter
		void			resetRot() {_rotAngle = vec3(0,0,0);};
		void			rotateX();
		void			rotateY();
		void			rotateZ();
	private:
		ParticlesGPU*	_particlesGPU;
		unsigned int	_particles;
		Camera			_camera;
		// Blending of Texture
		const float		_rotationSpeed = 100.f;
		// Rotations
		vec3			_rotationsEnable;
		vec3			_rotAngle;
		vec3			_rotations;


		void applyRotation(float deltaTime);
};

#endif