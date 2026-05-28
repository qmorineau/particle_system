#ifndef SIMULATIONSTATE_HPP
#define SIMULATIONSTATE_HPP

class SimulationState
{
	public:
		enum class MouseTarget
		{
			Emitter,
			Gravity,
			Camera,
			Free
		};
		enum class ColorMode
		{
			Mouse,
			Gravity,
			Emitter,
			Fire,
			COUNT
		};
		enum class ParticlesMode
		{
			Default = -1,
			Smoke = 0,
			Magic = 1
		};
		SimulationState(unsigned int particles);
		~SimulationState();

		void			accelerateTimeSpeed(); 
		void			slowTimeSpeed();
		void			changeColorMode();
		void			addParticles();
		void			removeParticles();
		
		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			toggleEmitter() {_isEmitter = !_isEmitter;};
		void			setMouseTarget(MouseTarget target) {_mouseTarget = target;};
		void			setParticlesMode(ParticlesMode m) {_particlesMode = m;};
		// getter
		unsigned int	count() const {return _particlesNbr;};
		unsigned int	maxParticles() const {return _particlesMax;};
		bool			isGravity() const {return _isGravity;};
		bool			isEmitter() const {return _isEmitter;};
		float			timeSpeed() const {return _timeSpeed;};
		float			lifespan() const {return _lifespan;};
		MouseTarget		mouseTarget() const {return _mouseTarget;};
		ColorMode		colorMode() const {return _colorMode;};
		ParticlesMode	particlesMode() const {return _particlesMode;};

	private:
		const unsigned int	_particlesIncr = 1000;
		const unsigned int	_particlesMax;
		long				_particlesNbr;
		bool				_isGravity = false;
		bool				_isEmitter = false; 
		float				_timeSpeed = 1.f;
		float				_lifespan = 3.f;
		MouseTarget			_mouseTarget = MouseTarget::Camera;
		ColorMode			_colorMode = ColorMode::Mouse;
		ParticlesMode		_particlesMode = ParticlesMode::Default;
};

#endif