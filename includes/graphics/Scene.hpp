#ifndef SCENE_HPP
#define SCENE_HPP

#include "Types.hpp"
#include "Camera.hpp"
#include "CameraGPU.hpp"

class ParticlesGPU;
class EmitterGPU;

class Scene
{
	public:
		enum PosTracked
		{
			Emitter,
			Gravity,
			None
		};
		Scene(unsigned int);
		~Scene();

		void update(float deltaTime, const vec2& mouseNDC);

		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			toggleEmitter() {_isEmitter = !_isEmitter;};
		void			accelerateTimeSpeed(); 
		void			slowTimeSpeed();
		void			shotEmitter() {_newEmitter = true;};
		void			setTrackPos(PosTracked track) {_track = track;};

		// getter
		Camera&			camera() {return _camera;};
		const Camera&	camera() const {return _camera;};
		ParticlesGPU&	particles() const {return *_particlesGPU;};
		EmitterGPU&		emitter() const {return *_emitterGPU;};
		int				getParticles() const {return _particles;};
		bool			getGravity() const {return _isGravity;};
		bool			getEmitter() const {return _isEmitter;};
		bool			getNewEmitter() const {return _newEmitter;};
		float			getTimeSpeed() const {return _timeSpeed;};
		float			getLifespan() const {return _lifespan;};
		PosTracked		getTracking() const {return _track;};
	private:
		ParticlesGPU*	_particlesGPU;
		EmitterGPU*		_emitterGPU;
		CameraGPU		_cameraGPU;
		unsigned int	_particles;
		PosTracked		_track = None;
		Camera			_camera;
		bool			_isGravity = false;
		bool			_isEmitter = false;
		bool			_newEmitter = false;
		float			_timeSpeed = 1.f;
		float			_lifespan = 3.f;

		void applyRotation(float deltaTime);
};

#endif