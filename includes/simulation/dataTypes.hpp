#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include "Types.hpp"

// each struct need to be 16 bytes aligned for glsl 430

struct Particle
{
	vec4 	position; 		// 16 bytes
	vec4 	velocity; 		// 16 bytes
	vec4 	color;			// 16 bytes
	float	lifeTime;		// 4 bytes
	float	timeToDeath;	// 4 bytes
	int		isDead;			// 4 bytes
	float	size;		// 4 bytes

	static constexpr unsigned int binding = 0;
};

struct Emitter
{
	vec4 positions;

	static constexpr unsigned int binding = 2;
};

struct Gravity
{
	vec4 positions;

	static constexpr unsigned int binding = 3;
};

#endif