#version 430

in vec3 texcoord;

uniform samplerCube tex_skybox;

void main()
{
	gl_FragColor = vec4(vec3(texture(tex_skybox,texcoord)),1.0f);
}