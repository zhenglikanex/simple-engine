#version 430

in vec2 frag_tex_coord;
in vec3 frag_normal;
in vec3 frag_position;
uniform sampler2D tex_diffuse;

#define MAX_DIRECTIONAL_LIGHT_COUNT 5
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

struct DirectionalLight
{
	vec3 directional;
	vec3 color;
	float intensity;
};

uniform DirectionalLight directional_lights[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform PointLight point_lights[MAX_POINT_LIGHT_COUNT];

vec3 ComputeLighting(vec3 frag_color,vec3 light_color,vec3 frag_to_light_dir,float intensity)
{

	// diffuse
    // 片段至光源的方向与法线的的点积
    vec3 normal = normalize(frag_normal);
	
	//计算漫反射率
    float diff = max(dot(normal, frag_to_light_dir), 0.0);
    vec3 diffuse = light_color * (diff * frag_color * intensity);
	
	return diffuse;
}

// 计算光照
vec3 ComputeDireactionalLighting(vec3 frag_color,DirectionalLight light)
{
	// 计算片段到灯光的方向
	vec3 frag_to_light_dir = normalize(-light.directional);
	return ComputeLighting(frag_color,light.color,frag_to_light_dir,light.intensity);
}

vec3 ComputePointLighting(vec3 frag_color,PointLight light)
{
	// 计算片段到灯光的方向
	vec3 frag_to_light_dir = normalize(light.position - frag_position);
	return ComputeLighting(frag_color,light.color,frag_to_light_dir,light.intensity);
}

void main()
{
	int point_light_count = 1;
	int directional_light_count = 1;

	vec3 frag_color = vec3(texture(tex_diffuse,frag_tex_coord));
	
	// 最终的颜色
	vec3 final_frag_color = frag_color * vec3(1.0,1.0,1.0);
	
	for(int i = 0;i< directional_light_count;i++)
	{
		final_frag_color = final_frag_color + ComputeDireactionalLighting(frag_color,directional_lights[i]);
	}
	
	for(int i = 0;i < point_light_count;i++)
	{
		final_frag_color = final_frag_color + ComputePointLighting(frag_color,point_lights[i]);
	}
	
	gl_FragColor = vec4(final_frag_color,1.0);
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}