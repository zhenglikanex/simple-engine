#version 430

in vec2 frag_tex_coord;

uniform sampler2D tex_hdr;
uniform float exposure;

void main()
{
	const float gamma = 2.2;
	vec3 hdr_color = texture(tex_hdr,frag_tex_coord).rgb;
	
	//曝光色调映射
	vec3 mapped = vec3(1.0) - exp(-hdr_color * exposure);
	
	//mapped = pow(mapped,vec3(1.0 / gamma));
	
	gl_FragColor = vec4(mapped,1.0);
}