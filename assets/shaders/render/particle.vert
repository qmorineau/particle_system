#version 430 core

// vao / vbo
layout (location = 0) in vec4 aPos;
layout (location = 2) in vec4 aColor;
layout (location = 3) in float aLifeTime;
layout (location = 4) in float aTimeToDeath;
layout (location = 5) in int aIsDead;
layout (location = 6) in float aSize;

// ubo / ssbo
layout(std140, binding = 1) uniform CameraData {
    mat4 uProjection;
    mat4 uView;
    vec3 uViewPos;
    float _pad0;
    vec2 uMouseNDC;
    float uNear;
    float uFar;
};

struct Emitter
{
	vec4 pos;
};
layout(std430, binding = 2) buffer EmitterBuff { Emitter emitter; };

struct Gravity
{
	vec4 pos;
};
layout(std430, binding = 3) buffer GravityBuff { Gravity gravity; };

// out for frag shader
out vec4 frag_col;

// uniform
uniform int color_mode;
uniform int track_mouse;
uniform float life_span;
uniform int particles_mode;

// variables
const int COLOR_MODE_MOUSE = 0;
const int COLOR_MODE_GRAVITY = 1;
const int COLOR_MODE_EMITTER = 2;
const int COLOR_MODE_FIRE = 3;

// textures
const int PARTICLE_MODE_DEFAULT = -1;
const int PARTICLE_MODE_SMOKE = 0;
const int PARTICLE_MODE_MAGIC = 1;
flat out int v_texID;
flat out vec4 v_color;

// func
vec3 mouseColorMode()
{
	vec3 color;
	vec2 mouseNDC = vec2(0, 0);
	if (track_mouse == 1)
		mouseNDC = uMouseNDC;
	vec4 world = vec4(aPos.xyz, 1.0f);
	vec4 clip = uProjection * uView * world;
	vec3 ndc = vec3(clip) / clip.w;
	float d = length(ndc.xy - mouseNDC);
	float t = clamp(d * 0.5, 0.0, 1.0);
	color = vec3(t, 1.0 - t, 0.5 - t);
	return color;
}

vec3 gravityColorMode()
{
	vec3 color;
	float dGrav = distance(aPos.xyz, gravity.pos.xyz);
	float distRatio = dGrav / 100.0;

	if (distRatio < 0.1)
		color = mix(vec3(0.6, 0.6, 0.8), vec3(0.3, 0.5, 0.8), distRatio / 0.2);
	else if (distRatio < 0.5)
		color = mix(vec3(0.3, 0.5, 0.8), vec3(0.0, 0.0, 0.8), (distRatio - 0.2) / 0.3);
	else if (distRatio < 0.8)
		color = mix(vec3(0.0, 0.0, 0.8), vec3(0.0, 0.0, 0.6), (distRatio - 0.5) / 0.3);
	else
		color = mix(vec3(0.0, 0.0, 0.6), vec3(0.0, 0.0, 0.2), (distRatio - 0.8) / 0.2);
	return color;
}

vec3 emitterColorMode()
{
	vec3 color;
	float dEmit = distance(aPos.xyz, emitter.pos.xyz);
	float distRatio = dEmit / 150.0;

	if (distRatio < 0.1)
		color = mix(vec3(1.0, 1.0, 0.8), vec3(0.5, 0.8, 0.3), distRatio / 0.2);
	else if (distRatio < 0.5)
		color = mix(vec3(0.5, 0.8, 0.3), vec3(0.0, 0.6, 0.0), (distRatio - 0.2) / 0.3);
	else if (distRatio < 0.8)
		color = mix(vec3(0.0, 0.6, 0.0), vec3(0.0, 0.4, 0.0), (distRatio - 0.5) / 0.3);
	else
		color = mix(vec3(0.0, 0.6, 0.0), vec3(0.0, 0.2, 0.0), (distRatio - 0.8) / 0.2);
	return color;
}

vec3 fireColorMode()
{
	vec3 color;
	float lifeRatio = aLifeTime / life_span;
	if (lifeRatio < 0.2)
		color = mix(vec3(1.0, 1.0, 0.8), vec3(1.0, 0.8, 0.0), lifeRatio / 0.2);
	else if (lifeRatio < 0.5)
		color = mix(vec3(1.0, 0.8, 0.0), vec3(1.0, 0.4, 0.0), (lifeRatio - 0.2) / 0.3);
	else if (lifeRatio < 0.8)
		color = mix(vec3(1.0, 0.4, 0.0), vec3(0.8, 0.1, 0.0), (lifeRatio - 0.5) / 0.3);
	else
		color = mix(vec3(0.8, 0.1, 0.0), vec3(0.2, 0.0, 0.0), (lifeRatio - 0.8) / 0.2);
	float heat = 1.0 - clamp(length(aPos.xyz) / 2.0, 0.0, 1.0);
	color = mix(color, vec3(1.0, 0.9, 0.7), heat * 0.3);
	return color;
}

vec3 calculate_color()
{
	vec3 color;
	switch (particles_mode)
	{
		case PARTICLE_MODE_SMOKE:
			color = aColor.xyz;
			break;
		case PARTICLE_MODE_MAGIC:
			//color = vec3(1, 0, 1);
			color = aColor.xyz;
			break;
		default:
			switch (color_mode)
			{
				case COLOR_MODE_MOUSE:
					color = mouseColorMode();
					break;
				case COLOR_MODE_GRAVITY:
					color = gravityColorMode();
					break;
				case COLOR_MODE_EMITTER:
					color = emitterColorMode();
					break;
				case COLOR_MODE_FIRE:
					color = fireColorMode();
					break;
				default:
					color = vec3(1,1,1);
					break;
			}
			break;
	}
	return color;
}

float calculate_transparency()
{
	switch (particles_mode)
	{
		case PARTICLE_MODE_SMOKE:
			float tmp = aLifeTime / life_span;
			if (tmp < 0.1)
				return tmp / 0.1 * 0.12;
			else if (tmp < 0.6)
				return 0.12;
			else if (tmp < 0.85)
				return mix(0.12, 0.04, (tmp - 0.6) / 0.25);
			else
				return mix(0.04, 0.0, (tmp - 0.85) / 0.15);
		case PARTICLE_MODE_MAGIC:
			return 1.0;
		default:
			return 1.0;
	}
}

float calculate_size()
{
	if (aIsDead == 1)
		return  0.0;
	else if (v_texID >= 0)
	{
		float dist = length(uViewPos - aPos.xyz);
        return clamp((aSize / dist) * 100.0, 1.0, 256.0);
	}
	else
	    return  1.0;
}

void main()
{
	v_texID = particles_mode;
    gl_Position = uProjection * uView * vec4(aPos.xyz, 1.0);
	gl_PointSize = calculate_size();
	frag_col = vec4(calculate_color(), calculate_transparency());
}
