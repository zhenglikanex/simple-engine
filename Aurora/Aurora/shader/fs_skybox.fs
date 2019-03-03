#version 430

in vec3 texcoord;

uniform samplerCube tex_skybox;

void main()
{
	gl_FragColor = texture(tex_skybox,texcoord);
}