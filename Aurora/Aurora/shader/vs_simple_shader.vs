#version 430

#define MAX_DIRECTIONAL_LIGHT_COUNT 5
#define MAX_POINT_LIGHT_COUNT 10

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;

uniform mat4 model_matrix;
uniform mat4 camera_matrix;
uniform mat4 proj_matrix;

uniform int dir_light_count;

uniform mat4 dl_space_matrixs[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform mat4 pl_view_matrixs[MAX_POINT_LIGHT_COUNT];

out vec2 frag_tex_coord;
out vec3 frag_normal;
out vec3 frag_position;
out vec4 dl_space_pos[MAX_DIRECTIONAL_LIGHT_COUNT];

void main()
{
	gl_Position = proj_matrix * camera_matrix * model_matrix * vec4(pos.x,pos.y,pos.z,1.0);
	frag_tex_coord = tex_coord;
	frag_normal = normal;
	frag_position = vec3(model_matrix * vec4(pos.x,pos.y,pos.z,1.0));
	
	for(int i = 0;i < dir_light_count;++i)
	{
		dl_space_pos[i] = dl_space_matrixs[i] * vec4(frag_position,1.0);
	}
}