#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include "Types.hpp"
#include "Camera.hpp"
#include "CameraGPU.hpp"

class ParticlesGPU;
class EmitterGPU;
class GravityGPU;

class Scene
{
	public:
		enum PosTracked
		{
			Emitter,
			Gravity,
			None
		};
		enum ColorMode
		{
			Mouse,
			Grav,
			Emit,
			COUNT
		};
		Scene(unsigned int);
		~Scene();

		void update(float deltaTime, const vec2& mouseNDC);

		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			toggleEmitter() {_isEmitter = !_isEmitter;};
		void			accelerateTimeSpeed(); 
		void			slowTimeSpeed();
		void			setTrackPos(PosTracked track) {_track = track;};
		void			changeColorMode();

		// getter
		Camera&			camera() {return _camera;};
		const Camera&	camera() const {return _camera;};
		ParticlesGPU&	particles() const {return *_particlesGPU;};
		EmitterGPU&		emitter() const {return *_emitterGPU;};
		GravityGPU&		gravity() const {return *_gravityGPU;};
		int				getParticles() const {return _particles;};
		bool			getGravity() const {return _isGravity;};
		bool			getEmitter() const {return _isEmitter;};
		float			getTimeSpeed() const {return _timeSpeed;};
		float			getLifespan() const {return _lifespan;};
		PosTracked		getTracking() const {return _track;};
		ColorMode		getColorMode() const {return _colorMode;};
	private:
		std::unique_ptr<ParticlesGPU>	_particlesGPU;
		std::unique_ptr<EmitterGPU>		_emitterGPU;
		std::unique_ptr<GravityGPU>		_gravityGPU;
		CameraGPU						_cameraGPU;
		
		unsigned int	_particles;
		PosTracked		_track = None;
		ColorMode		_colorMode = Mouse;
		Camera			_camera;
		bool			_isGravity = false;
		bool			_isEmitter = false; 
		float			_timeSpeed = 1.f;
		float			_lifespan = 3.f;

		void applyRotation(float deltaTime);
};

#endif