#include "SubMesh.h"

#include "Mesh.h"

namespace aurora
{
	SubMesh::SubMesh(const VertexBufferPtr& vertex_buffer, const IndexBufferPtr& index_buffer)
		:vertex_buffer_(vertex_buffer)
		,index_buffer_(index_buffer)
	{
		vao_ = MakeVertexArrayObjectPtr(vertex_buffer_, index_buffer_);
	}

	SubMesh::SubMesh(const VertexBufferPtr& vertex_buffer, const IndexBufferPtr& index_buffer, const MaterialPtr& material_ptr)
		: vertex_buffer_(vertex_buffer)
		, index_buffer_(index_buffer)
		, material_ptr_(material_ptr)
	{
		vao_ = MakeVertexArrayObjectPtr(vertex_buffer_, index_buffer_);
	}

	SubMesh::~SubMesh()
	{

	}

	// 得到网格的面数
	uint32_t SubMesh::GetFaceCount()
	{
		return index_buffer_->index_count() / 3;
	}

	RenderOperation SubMesh::GetRenderOperation()
	{
		return RenderOperation(RenderOperation::OT_TRIANGLE_LIST,vao_);
	}
}