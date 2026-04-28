#ifndef SCENE_HPP
#define SCENE_HPP

#include "Types.hpp"
#include "Camera.hpp"

class Scene
{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

		// getter
		Camera&			camera() {return _camera;};
		const vec3&		getRotAngle() const {return _rotAngle;};
		// setter
		void			resetRot() {_rotAngle = vec3(0,0,0);};
		void			rotateX();
		void			rotateY();
		void			rotateZ();
	private:
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