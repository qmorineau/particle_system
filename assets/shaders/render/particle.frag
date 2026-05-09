#version 430 core

in vec4 frag_col;
out vec4 out_col;

void main()
{
    vec2 c = gl_PointCoord - 0.5;
	out_col = frag_col;
}