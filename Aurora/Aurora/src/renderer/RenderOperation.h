#ifndef RENDER_OPERATOR_H_
#define RENDER_OPERATOR_H_

#include "VertexLayout.h"

namespace aurora
{
	class RenderOperation
	{
	public:
		enum OperationType
		{
			/// A list of points, 1 vertex per point
			OT_POINT_LIST = 1,
			/// A list of lines, 2 vertices per line
			OT_LINE_LIST = 2,
			/// A strip of connected lines, 1 vertex per line plus 1 start vertex
			OT_LINE_STRIP = 3,
			/// A list of triangles, 3 vertices per triangle
			OT_TRIANGLE_LIST = 4,
			/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
			OT_TRIANGLE_STRIP = 5,
			/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
			OT_TRIANGLE_FAN = 6,
		};
		
		RenderOperation(OperationType operation_type,const VertexArrayObject& vao)
			:operation_type_(operation_type)
			, vao_(vao)
		{
			
		}

		OperationType operation_type() const { return operation_type_; }
		const VertexArrayObject& vao() const { return vao_; }
	private:
		OperationType operation_type_;
		VertexArrayObject vao_;
	};
}

#endif
