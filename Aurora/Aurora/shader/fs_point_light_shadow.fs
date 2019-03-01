#version 430
in vec4 frag_pos;

uniform vec3 light_pos;
uniform float far_plane;

void main()
{
	float light_distance = length(frag_pos.xyz - light_pos);
	
	// 映射到[0,1]范围
	light_distance /= far_plane;
	
	// 显示写入深度
	gl_FragDepth = 0.5;
}