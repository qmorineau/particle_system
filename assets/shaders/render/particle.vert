#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 2) in vec4 aColor;

layout(std140, binding = 1) uniform CameraData {
    mat4 uProjection;
    mat4 uView;
    vec3 uViewPos;
    float _pad0;
    vec2 uMouseNDC;
    float uNear;
    float uFar;
};

out vec4 frag_col;

void main()
{
    gl_Position = uProjection * uView * vec4(aPos.xyz, 1.0);
    gl_PointSize = 1.0;
    frag_col = aColor;
}
