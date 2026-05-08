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
			COUNT
		};
		SimulationState();
		~SimulationState();

		void			accelerateTimeSpeed(); 
		void			slowTimeSpeed();
		void			changeColorMode();
		
		// setter
		void			toggleGravity() {_isGravity = !_isGravity;};
		void			toggleEmitter() {_isEmitter = !_isEmitter;};
		void			setMouseTarget(MouseTarget target) {_mouseTarget = target;};
		// getter
		bool			isGravity() const {return _isGravity;};
		bool			isEmitter() const {return _isEmitter;};
		float			timeSpeed() const {return _timeSpeed;};
		float			lifespan() const {return _lifespan;};
		MouseTarget		mouseTarget() const {return _mouseTarget;};
		ColorMode		colorMode() const {return _colorMode;};

	private:
		bool			_isGravity = false;
		bool			_isEmitter = false; 
		float			_timeSpeed = 1.f;
		float			_lifespan = 3.f;
		MouseTarget		_mouseTarget = MouseTarget::Camera;
		ColorMode		_colorMode = ColorMode::Mouse;
};

#endif