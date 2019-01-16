#version 430

layout(location=0) in vec3 position;

uniform mat4 light_view;
uniform mat4 projection;
uniform mat4 model_matrix;

void main()
{
	gl_Position = projection * light_view * model_matrix * vec4(position,1.0f);
}