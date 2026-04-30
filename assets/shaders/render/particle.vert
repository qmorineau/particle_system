#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 2) in vec4 aColor;

uniform mat4 view;
uniform mat4 projection;

out vec4 frag_col;

void main()
{
    gl_Position = projection * view * vec4(aPos.xyz, 1.0);
    gl_PointSize = 1.0;
    frag_col = aColor;
}
