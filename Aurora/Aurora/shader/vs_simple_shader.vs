#version 430
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 tangent;
layout(location = 3) in vec3 bitangent;

uniform mat4 model_matrix;
uniform mat4 camera_matrix;
uniform mat4 proj_matrix;

out vec2 frag_tex_coord;
out vec3 frag_normal;
out vec3 frag_position;
void main()
{
	gl_Position = proj_matrix * camera_matrix * model_matrix * vec4(pos.x,pos.y,pos.z,1.0);
	frag_tex_coord = tex_coord;
	frag_normal = normal;
	frag_position = vec3(model_matrix * vec4(pos.x,pos.y,pos.z,1.0));
}