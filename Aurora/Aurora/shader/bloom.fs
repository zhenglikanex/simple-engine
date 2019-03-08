#version 430

in vec2 frag_tex_coords;

uniform sampler2D tex_bloom;
uniform sampler2D tex_hdr;

void main()
{
	vec4 color = texture(tex_hdr,frag_tex_coords) + texture(tex_bloom,frag_tex_coords);
	gl_FragColor = vec4(color.rgb,1.0);
}