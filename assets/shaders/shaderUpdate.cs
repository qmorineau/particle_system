#version 430 core

layout(local_size_x = 256) in;

struct Particle
{
    vec4 pos;
    vec4 vel;
    vec4 col;
};

layout(std430, binding = 0) buffer Particles { Particle particles[]; };

uniform vec3  gravity_pos;
uniform int   gravity_on;
uniform float delta_time;
uniform int   particles_nbr;

float hash(uint x)
{
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    x ^= x >> 16;
    return float(x) / float(0xffffffffu);
}

void main()
{
    uint i = gl_GlobalInvocationID.x;
    if (i >= particles_nbr) return;

    // ---------------------------------------------------------
    // INITIALISATION GPU (une seule fois)
    // ---------------------------------------------------------
    // Le SSBO est rempli de zéros au début → pos.w == 0.0
    if (particles[i].pos.w == 0.0)
    {
        // Génération pseudo-aléatoire basée sur l'indice i
        float rx = hash(i * 123u);
        float ry = hash(i * 456u);
        float rz = hash(i * 789u);

        // Position dans un cube [-1, 1]
        particles[i].pos = vec4(rx * 2.0 - 1.0,
                                ry * 2.0 - 1.0,
                                rz * 2.0 - 1.0,
                                1.0);

        // Vitesse initiale nulle
        particles[i].vel = vec4(0.0);

        // Couleur blanche au début
        particles[i].col = vec4(1.0, 1.0, 1.0, 1.0);

        return; // On ne fait pas la physique la première frame
    }

    // ---------------------------------------------------------
    // PHYSIQUE NORMALE
    // ---------------------------------------------------------

    vec3 pos = particles[i].pos.xyz;
    vec3 vel = particles[i].vel.xyz;

    // Force gravitationnelle
    vec3 dir  = gravity_pos - pos;
    float dist = length(dir) + 0.1;
    vec3 force = normalize(dir) * (50.0 / (dist * dist));
    vel += force * delta_time * gravity_on;

    // Intégration
    pos += vel * delta_time;

    // Couleur selon distance
    // float d = clamp(dist / 20.0, 0.0, 1.0);
    // particles[i].col = vec4(1.0 - d, 0.3, d, 1.0);

    // Écriture
    particles[i].pos.xyz = pos;
    particles[i].vel.xyz = vel;
}
