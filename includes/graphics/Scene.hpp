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
		// getter
		Camera&			camera() {return _camera;};
		ParticlesGPU&	particles() const {return *_particlesGPU;};
		int				getParticles() const {return _particles;};
		bool			getGravity() const {return _isGravity;};
	private:
		ParticlesGPU*	_particlesGPU;
		unsigned int	_particles;
		Camera			_camera;
		bool			_isGravity = false;

		void applyRotation(float deltaTime);
};

#endif