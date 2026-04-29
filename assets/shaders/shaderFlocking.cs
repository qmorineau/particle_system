#version 430 core
layout(local_size_x = 256) in;

struct Particle {
    vec4 pos;
    vec4 vel;
    vec4 col;
};

layout(std430, binding = 0) buffer Particles {
    Particle particles[];
};

uniform int particles_nbr;
uniform float delta_time;
uniform float sphereRadius;

// Flocking params
const float neighborRadius   = 1.5;
const float separationRadius = 0.25;
const float maxSpeed         = 1.2;

const float alignmentWeight  = 0.6;
const float cohesionWeight   = 0.25;
const float separationWeight = 2.0;


void main()
{
    uint i = gl_GlobalInvocationID.x;
    if (i >= uint(particles_nbr)) return;

    // -------------------------
    // INIT (one time)
    // -------------------------
    if (particles[i].vel.x == 0.0 &&
        particles[i].vel.y == 0.0 &&
        particles[i].vel.z == 0.0)
    {
        float rx = fract(sin(i * 12.9898) * 43758.5453) * 2.0 - 1.0;
        float ry = fract(sin(i * 78.233)  * 19341.1234) * 2.0 - 1.0;
        float rz = fract(sin(i * 45.123)  * 91823.1234) * 2.0 - 1.0;

        vec3 dir = normalize(vec3(rx, ry, rz));
        float r = fract(sin(i * 0.1234) * 99999.0) * sphereRadius * 0.8;

        particles[i].pos = vec4(dir * r, 1.0);

        particles[i].vel = vec4(
            fract(sin(i * 1.234)) * 0.5,
            fract(sin(i * 5.678)) * 0.5,
            fract(sin(i * 9.101)) * 0.5,
            0.0
        );

        particles[i].col = vec4(1,1,1,1);
        return;
    }

    // -------------------------
    // FLOCKING
    // -------------------------
    vec3 pos = particles[i].pos.xyz;
    vec3 vel = particles[i].vel.xyz;

    vec3 align = vec3(0);
    vec3 coh   = vec3(0);
    vec3 sep   = vec3(0);
    int count  = 0;

    float minDist = 99999.0;

    for (int j = 0; j < particles_nbr; j++)
    {
        if (j == int(i)) continue;

        vec3 op = particles[j].pos.xyz;
        vec3 ov = particles[j].vel.xyz;

        vec3 diff = op - pos;
        float d = length(diff);

        // Track closest neighbor
        if (d < minDist && d > 0.0001)
            minDist = d;

        if (d < neighborRadius)
        {
            count++;

            align += ov;
            coh   += op;

            if (d < separationRadius)
                sep -= diff / max(d, 0.001);
        }
    }

    if (count > 0)
    {
        float inv = 1.0 / float(count);

        align = normalize(align * inv) * maxSpeed - vel;
        coh   = (coh * inv - pos);

        vel += alignmentWeight  * align
             + cohesionWeight   * coh
             + separationWeight * sep;
    }

    // Limit speed
    float s = length(vel);
    if (s > maxSpeed)
        vel *= maxSpeed / s;

    // Update position
    pos += vel * delta_time;

    // -------------------------
    // SPHERE CONTAINMENT
    // -------------------------
    float dist = length(pos);

    if (dist > sphereRadius)
    {
        vec3 toCenter = normalize(-pos);
        float excess = dist - sphereRadius;

        vel += toCenter * (excess * 0.3);
        pos += toCenter * (excess * 0.1);
    }

    // -------------------------
    // COLOR BASED ON NEAREST NEIGHBOR
    // -------------------------
    float t = clamp(minDist / neighborRadius, 0.0, 1.0);

    vec3 col = mix(
        vec3(1.0, 0.2, 0.1),  // close = red
        vec3(0.1, 0.2, 1.0),  // far = blue
        t
    );

    particles[i].col = vec4(col, 1.0);

    // -------------------------
    // WRITE BACK
    // -------------------------
    particles[i].pos = vec4(pos, 1.0);
    particles[i].vel = vec4(vel, 0.0);
}
