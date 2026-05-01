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

		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			setGravityPos(vec3 pos) {_gravityPos = pos;};
		// getter
		Camera&			camera() {return _camera;};
		const Camera&	camera() const {return _camera;};
		ParticlesGPU&	particles() const {return *_particlesGPU;};
		int				getParticles() const {return _particles;};
		bool			getGravity() const {return _isGravity;};
		vec3			getGravityPos() const {return _gravityPos;};
	private:
		ParticlesGPU*	_particlesGPU;
		unsigned int	_particles;
		Camera			_camera;
		vec3			_gravityPos;
		bool			_isGravity = false;

		void applyRotation(float deltaTime);
};

#endif