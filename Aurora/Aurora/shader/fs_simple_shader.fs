#version 430

#define MAX_DIRECTIONAL_LIGHT_COUNT 5
#define MAX_POINT_LIGHT_COUNT 10

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec4 BrigthColor;

in vec2 frag_tex_coord;
in vec3 frag_normal;
in vec3 frag_position;
in vec4 dl_space_pos[MAX_DIRECTIONAL_LIGHT_COUNT];
uniform sampler2D tex_diffuse;
uniform sampler2D tex_dl_shadow;
uniform vec3 camera_position;
uniform int dir_light_count;

uniform samplerCube tex_pl_shadow;
uniform float far_plane;

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
	
	// 当前片元在灯光空间下的深度
	float current_depth = proj_coords.z;
	
	float bias = 0.005;
	float shadow = 0.0;
	vec2 texel_size = 1.0 / textureSize(tex_dl_shadow,0);
	
	for(int x = 0;x<=0;++x)
	{
		for(int y = 0;y <= 0;++y)
		{
			float pfc_depth = texture(tex_dl_shadow,proj_coords.xy + vec2(x,y) * texel_size).r;
			shadow += current_depth - bias > pfc_depth ? 1.0 : 0.0;
		}
	}
	
	shadow /= 1.0;
	
	return shadow;
	
	/*
	// 获得最近的纹理
	float closest_depth = texture(tex_dl_shadow,proj_coords.xy).r;
		
	// 比较当前深度和最近的深度，如果在最近的深度后面，则在阴影下
	float bias = 0.005;
	//float bias = max(0.05 * (1.0 - dot(normalize(frag_normal), light_dir)), 0.005);
	return current_depth - bias > closest_depth ? 1.0 : 0.0;
	*/
}

float PointShadowCalculation(vec3 frag_pos,vec3 light_pos)
{
	vec3 light_to_frag = frag_pos - light_pos;
	//float closest_depth = texture(tex_pl_shadow,light_to_frag).r;
	//closest_depth *= far_plane;
	float current_depth = length(light_to_frag);
	/*
    float shadow = current_depth - 0.05 > closest_depth ? 1.0 : 0.0;
    return shadow;
	*/
	
	/*
	float shadow = 0.0;
	float bias = 0.05; 
	float samples = 4.0;
	float offset = 0.1;
	
	for(float x = -offset; x < offset;x += offset / (samples * 0.5))
	{
		for(float y = -offset;y < offset;y += offset / (samples * 0.5))
		{
			for(float z = -offset; z < offset; z += offset / (samples * 0.5))
			{
				float closest_depth = texture(tex_pl_shadow,light_to_frag + vec3(x,y,z)).r;
				closest_depth *= far_plane;
				if(current_depth - bias > closest_depth)
				{
					shadow += 1.0;
				}
			}
		}
	}
	*/
	vec3 sample_offeset_directions[20] = vec3[]
	(
		vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
		vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
		vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
		vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
		vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
	);
	
	float shadow = 0.0;
	float bias = 0.1;
	int samples = 20;
	float view_distance = length(camera_position - frag_pos);
	
	//我们可以基于观察者里一个fragment的距离来改变diskRadius；这样我们就能根据观察者的距离来增加偏移半径了，当距离更远的时候阴影更柔和，更近了就更锐利。
	float disk_radius = (1.0 + (view_distance / far_plane)) / 25.0;
	//float disk_radius = 0.05;
	
	for(int i = 0;i < samples;++i)
	{
		float closest_depth = texture(tex_pl_shadow,light_to_frag + sample_offeset_directions[i] * disk_radius).r;
		closest_depth *= far_plane;
		if(current_depth - bias > closest_depth)
		{
			shadow += 1.0;
		}
	}
	
	return shadow / samples;
}

void main()
{
	//vec3 light_to_frag = frag_position - point_lights[0].position;
	//gl_FragColor = vec4(vec3(texture(tex_pl_shadow,light_to_frag).r),1.0);

	int point_light_count = 1;

	vec3 frag_color = vec3(texture(tex_diffuse,frag_tex_coord));
	
	// 最终的颜色
	vec3 final_frag_color = frag_color * vec3(0.1,0.1,0.1);
	
	for(int i = 0;i< dir_light_count;i++)
	{
		float shadow = ShadowCalculation(dl_space_pos[i]);
		final_frag_color = final_frag_color + (1.0 - shadow) * ComputeDireactionalLighting(frag_color,directional_lights[i]);
	}
	
	for(int i = 0;i < point_light_count;i++)
	{
		float shadow = PointShadowCalculation(frag_position,point_lights[i].position);
		final_frag_color = final_frag_color + (1.0 - shadow) * ComputePointLighting(frag_color,point_lights[i]);
	}
	
	FragColor = vec4(final_frag_color,1.0);
	
	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
		
	//将过亮的颜色输出到BrightColor
	float brightness = dot(FragColor.rgb,vec3(0.2126,0.7152,0.0722));
	if(brightness > 1.0)
	{
		BrigthColor = vec4(FragColor.rgb,1.0);
	} 
	else 
	{
		BrigthColor = vec4(0,0,0,1);
	}
}