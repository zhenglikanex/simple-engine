#version 430

layout(location = 0) in vec3 pos;

uniform mat4 proj_matrix;
uniform mat4 camera_matrix;

out vec3 texcoord;

void main()
{
	texcoord = pos;
	vec4 position = proj_matrix * camera_matrix * vec4(pos,1.0f);
	gl_Position = position.xyww;
}