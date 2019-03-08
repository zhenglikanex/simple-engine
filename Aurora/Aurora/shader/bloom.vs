#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coords;

out vec2 frag_tex_coords;

void main()
{
	frag_tex_coords = tex_coords;
	gl_Position = vec4(pos,1.0);
}