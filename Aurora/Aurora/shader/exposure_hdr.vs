#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_coord;

out vec2 frag_tex_coord;

void main()
{
	frag_tex_coord = tex_coord;
	gl_Position = vec4(pos,1.0);
}