#version 430

layout(location=0) in position;

uniform light_view;
uniform projection;

void main()
{
	gl_Position = projection * light_view * position;
}