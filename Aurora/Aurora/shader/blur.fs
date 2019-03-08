#version 430

//layout(location = 0) out vec4 HorizontalColor;
//layout(location = 1) out vec4 VerticalColor;

in vec2 frag_tex_coords;

uniform sampler2D tex;

uniform bool horizontal;

void main()
{
	float widget[5] = { 0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216 };
	
	vec2 tex_offset = 1.0 / textureSize(tex,0);
	vec3 result = texture(tex,frag_tex_coords).rgb * widget[0];
	int count = 5;
	if(horizontal)
	{
		for(int i = 1;i<5;++i)
		{
			result += texture(tex,frag_tex_coords + vec2(tex_offset.x * i,0)).rgb * widget[i];
			result += texture(tex,frag_tex_coords - vec2(tex_offset.x * i,0)).rgb * widget[i];
		}
		
		//HorizontalColor = vec4(result,1.0);
		//VerticalColor = vec4(0.0,0.0,0.0,1.0);
	}
	else
	{
		for(int i = 1;i<5;++i)
		{
			result += texture(tex,frag_tex_coords + vec2(0,tex_offset.y * i)).rgb * widget[i];
			result += texture(tex,frag_tex_coords - vec2(0,tex_offset.y * i)).rgb * widget[i];
		}

		//HorizontalColor = vec4(0.0,0.0,0.0,1.0);
		//VerticalColor = vec4(result,1.0);
	}
	
	gl_FragColor = vec4(result,1.0);
}