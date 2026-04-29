#version 430 core

layout(local_size_x = 256) in;

struct Particle
{
	vec3 pos;
	vec3 vel;
	vec3 col;
};

layout(std430, binding = 0) buffer Particles {Particle particles[];};

uniform vec3	gravity_pos;
uniform int		gravity_on;
uniform float	delta_time;
uniform int		particles_nbr;

void main()
{
    uint i = gl_GlobalInvocationID.x;  /* indice de cette particule */
    if (i >= particles_nbr) return;  /* garde-fou             */
 
    /* Lecture de l'état actuel */
    vec3 pos = particles[i].pos.xyz;
    vec3 vel = particles[i].vel.xyz;
 
    /* Force gravitationnelle vers l'attracteur */
    vec3 dir    = gravity_pos - pos;
    float dist  = length(dir) + 0.1;           /* +0.1 évite div/0  */
    vec3 force  = normalize(dir) * (50.0 / (dist * dist));
    vel += force * delta_time * gravity_on;
 
    /* Intégration d'Euler : nouvelle position */
    pos += vel * delta_time;
 
    /* Couleur selon distance à l'attracteur (bonus visuel) */
    float d = clamp(dist / 20.0, 0.0, 1.0);
    particles[i].col = vec3(1.0 - d, 0.3, d); /* rouge→bleu */
 
    /* Écriture dans le SSBO — même buffer que le vertex shader lit */
    particles[i].pos.xyz = pos;
    particles[i].vel.xyz = vel;
};