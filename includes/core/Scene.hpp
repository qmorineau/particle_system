#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>

#include "Types.hpp"
#include "Camera.hpp"
#include "CameraGPU.hpp"
#include "ParticleSystem.hpp"
#include "SimulationState.hpp"

class Scene
{
	public:
		Scene(unsigned int);
		~Scene();

		void update(float deltaTime, const vec2& mouseNDC);

		// getter
		Camera&					camera() {return _camera;};
		const Camera&			camera() const {return _camera;};
		SimulationState&		simulationState() {return _simulationState;};
		const SimulationState&	simulationState() const {return _simulationState;};
		ParticleSystem&			particleSystem() {return _particleSystem;};
		const ParticleSystem&	particleSystem() const {return _particleSystem;};

	private:
		ParticleSystem	_particleSystem;
		SimulationState	_simulationState;
		Camera			_camera;
		CameraGPU		_cameraGPU;
};

#endif