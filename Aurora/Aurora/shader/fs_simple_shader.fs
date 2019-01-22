#version 430

#define MAX_DIRECTIONAL_LIGHT_COUNT 5
#define MAX_POINT_LIGHT_COUNT 10

in vec2 frag_tex_coord;
in vec3 frag_normal;
in vec3 frag_position;
in vec4 dl_space_pos[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform sampler2D tex_diffuse;
uniform sampler2D tex_dl_shadow;

uniform int dir_light_count;

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

float ShadowCalculation(vec4 frag_dir_light_space)
{
    // 执行透视除法
    vec3 proj_coords = frag_dir_light_space.xyz / frag_dir_light_space.w;
	
	// 变换到纹理坐标范围[0,1]
	proj_coords = proj_coords * 0.5 + 0.5;
	
	// 获得最近的纹理
	float closest_depth = texture(tex_dl_shadow,proj_coords.xy).r;
	
	// 当前片元在灯光空间下的深度
	float current_depth = proj_coords.z;
	
	// 比较当前深度和最近的深度，如果在最近的深度后面，则在阴影下
	return current_depth > closest_depth ? 1.0 : 0.0;
}

void main()
{
	// 判断是否在阴影中
	float shadow = 0.0;
	for(int i = 0;i < dir_light_count;i++)
	{
		shadow = ShadowCalculation(dl_space_pos[i]);
		if(shadow > 0.0)
		{
			break;
		}
	}
	
	int point_light_count = 1;

	vec3 frag_color = vec3(texture(tex_diffuse,frag_tex_coord));
	
	// 最终的颜色
	vec3 final_frag_color = frag_color * vec3(0.5,0.5,0.5);
	
	for(int i = 0;i< dir_light_count;i++)
	{
		final_frag_color = final_frag_color + (1.0 - shadow) * ComputeDireactionalLighting(frag_color,directional_lights[i]);
	}
	
	for(int i = 0;i < point_light_count;i++)
	{
		final_frag_color = final_frag_color + ComputePointLighting(frag_color,point_lights[i]);
	}
	
	gl_FragColor = vec4(final_frag_color,1.0);
	
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}