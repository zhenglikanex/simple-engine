#version 430
layout(location = 0) in vec3 position;

uniform mat4 model_matrix;

void main()
{
	//gl_Position = model_matrix * vec4(position,1.0);
	gl_Position = vec4(position,1.0);
}