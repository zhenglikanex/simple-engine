#version 430

in vec2 frag_texcrood;

uniform sampler2D tex_shadow;

void main()
{
	//gl_FragColor = vec4(vec3(texture(tex_shadow,frag_texcrood)),1.0f);
	gl_FragColor = vec4(vec3(texture(tex_shadow,frag_texcrood).r),1.0f);
	//gl_FragColor = vec4(frag_texcrood,0.0f,1.0f);
	//gl_FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
	//gl_FragColor = vec4(1.0,0.0,0.0,0.5);
}