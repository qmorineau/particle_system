#version 430 core

in vec4 frag_col;
flat in int	v_texID;
out vec4 out_col;

uniform sampler2D textures[2];

void main()
{
    //vec2 c = gl_PointCoord - 0.5;
	if (v_texID < 0)
	{
		out_col = frag_col;
	}
	else
	{
		out_col = texture(textures[v_texID], gl_PointCoord) * frag_col;
	}
}