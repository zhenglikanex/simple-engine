#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcrood;

out vec2 frag_texcrood;

void main()
{
	gl_Position = vec4(position,1.0f);
	frag_texcrood = texcrood;
}