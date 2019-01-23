#version 430
layout(triangles) in;
layout(triangle_strip,max_vertices=18)out;

uniform mat4 light_view_matrixs[6];

out vec4 frag_pos;

void main()
{
	for(int face = 0;face < 6;++face)
	{
		gl_Layer = face;
		for(int i = 0;i < 3;++i)
		{
			frag_pos = gl_in[i].gl_Position;
			gl_Position = light_view_matrixs[face] * frag_pos;
			EmitVertex();
		}
		EndPrimitive();
	}
}