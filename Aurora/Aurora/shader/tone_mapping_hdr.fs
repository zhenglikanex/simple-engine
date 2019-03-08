#version 430

in vec2 frag_tex_coord;
uniform sampler2D tex_hdr;


void main()
{
	const float gamma = 2.2;
	vec3 hdr_color = texture(tex_hdr,frag_tex_coord).rgb;
	
	//Reinhard色调映射
	vec3 mapped = hdr_color / (hdr_color + vec3(1.0));
	
	// Gammed校正
	//mapped = pow(mapped,vec3(1.0 / gamma));
	
	gl_FragColor = vec4(mapped,1.0);
	//gl_FragColor = vec4(hdr_color,1.0);
}