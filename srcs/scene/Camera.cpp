#include "Camera.hpp"

Camera::Camera(int width, int height, vec3 position, vec3 up, float yaw, float pitch) : 
	_front(vec3(0.0f, 0.0f, -1.0f)), 
	_width(width), 
	_height(height),
	_target(0, 0, 0),
	_baseFront(_front),
	_baseUp(up),
	_basePosition(position)
{
	_mode = CameraMode::FREE;
	_aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
	_position = position;
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	updateCameraVectors();
}

void Camera::resize(int width, int height)
{
	_width = width;
	_height = height;
	_aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
}

void Camera::moveFreeMode(CameraMovement direction, float deltaTime)
{
	float velocity = _movementSpeed * deltaTime;
	if (direction == FORWARD)
		_position += _front * velocity;
	if (direction == BACKWARD)
		_position -= _front * velocity;
	if (direction == LEFT)
		_position -= _right * velocity;
	if (direction == RIGHT)
		_position += _right * velocity;
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
	switch (_mode)
	{
		case CameraMode::FREE:
			moveFreeMode(direction, deltaTime);
			break;
	}

}

void Camera::onMouseMove(const vec2& posIn)
{
	float xpos = static_cast<float>(posIn.x);
	float ypos = static_cast<float>(posIn.y);

	if (_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos;
	_lastX = xpos;
	_lastY = ypos;

	xoffset *= _mouseSensitivity;
	yoffset *= _mouseSensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	float clamp = 89.f;
	_pitch = _pitch < -clamp ? -clamp : _pitch > clamp ? clamp : _pitch;

	updateCameraVectors();
}

void Camera::onMouseScroll(const vec2& offset)
{
	_zoom -= static_cast<float>(offset.y);
	if (_zoom < 1.0f)
		_zoom = 1.0f;
	if (_zoom > 45.0f)
		_zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// calculate the new Front vector
	vec3 front;
	front.x = cos(math::radians(_yaw)) * cos(math::radians(_pitch));
	front.y = sin(math::radians(_pitch));
	front.z = sin(math::radians(_yaw)) * cos(math::radians(_pitch));
	_front = math::normalize(front);
	// also re-calculate the Right and Up vector
	_right = math::normalize(math::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	_up    = math::normalize(math::cross(_right, _front));
}

void Camera::resetPosition()
{
	changePosition(_basePosition);
	_firstMouse = true;
	updateOrientation();
}

void Camera::updateOrientation()
{
	switch (_mode)
	{
		case CameraMode::FREE:
		{
			_yaw   = math::degrees(atan2(_front.z, _front.x));
    		_pitch = math::degrees(asin(_front.y));
			break;
		}
	}
}

void Camera::changePosition(const vec3& pos)
{
    _position = pos;
    _front = math::normalize(_target - _position);
    _right = math::normalize(math::cross(_front, _worldUp));
    _up    = math::normalize(math::cross(_right, _front));
}
