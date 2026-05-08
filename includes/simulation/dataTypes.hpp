#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include "Types.hpp"

// each struct need to be 16 bytes aligned for glsl 430

struct Particle
{
	vec4 	position;
	vec4 	velocity;
	vec4 	color;
	float	lifeTime;
	float	timeToDeath;
	int		isDead;
	int		aligned;

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