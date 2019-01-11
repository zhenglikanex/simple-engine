#version 430

in vec2 frag_tex_coord;
in vec3 frag_normal;
in vec3 frag_position;
uniform sampler2D tex_diffuse;

#define MAX_POINT_LIGHT_COUNT 10

struct PointLight
{
	vec3 position;
	vec3 color;
	float intensity;
	float radius;
	float constant;     //kc
	float linear;       //kl
	float quadratic;    //kq
};

uniform PointLight point_lights[MAX_POINT_LIGHT_COUNT];

// 计算光照
vec3 ComputePointLighting(vec3 frag_color,PointLight light)
{
	// 计算片段到灯光的方向
	vec3 frag_to_light_dir = normalize(frag_position - light.position);

	// diffuse
    // 片段至光源的方向与法线的的点积
    vec3 normal = normalize(frag_normal);
	
	//计算漫反射率
    float diff = max(dot(normal, frag_to_light_dir), 0.0);
    vec3 diffuse = light.color * (diff * frag_color);
	
	return diffuse;
}

void main()
{	
	int point_light_count = 1;

	vec3 frag_color = vec3(texture(tex_diffuse,frag_tex_coord));
	
	// 最终的颜色
	vec3 final_frag_color = frag_color * vec3(1.0,1.0,1.0);
	
	for(int i = 0;i < point_light_count;i++)
	{
		final_frag_color = final_frag_color + ComputePointLighting(frag_color,point_lights[0]);
	}
	
	gl_FragColor = vec4(final_frag_color,1.0);
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}