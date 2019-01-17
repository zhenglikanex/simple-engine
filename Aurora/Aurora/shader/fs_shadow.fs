#version 430

void main()
{
	//gl_FragDepth = gl_FragCoord.z;		// 显示设置深度(可以不用，底层会默认设置深度缓冲)
	gl_FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
	
}