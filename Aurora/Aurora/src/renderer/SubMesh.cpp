#include "SubMesh.h"

#include "Mesh.h"

namespace aurora
{
	SubMesh::SubMesh(const MeshPtr& mesh_ptr, VertexBuffer&& vertex_buffer, IndexBuffer&& index_buffer)
		:mesh_weak_ptr_(mesh_ptr)
		,vertex_buffer_(std::move(vertex_buffer))
		,index_buffer_(std::move(index_buffer))
		,vao_(vertex_buffer_,index_buffer_)
	{

	}

	SubMesh::SubMesh(const MeshPtr& mesh_ptr, VertexBuffer&& vertex_buffer, IndexBuffer&& index_buffer, const MaterialPtr& material_ptr)
		: mesh_weak_ptr_(mesh_ptr)
		, vertex_buffer_(std::move(vertex_buffer))
		, index_buffer_(std::move(index_buffer))
		, material_ptr_(material_ptr)
		, vao_(vertex_buffer_, index_buffer_)
	{

	}

	SubMesh::~SubMesh()
	{

	}

	MeshPtr SubMesh::GetMesh()
	{
		if (mesh_weak_ptr_.expired())
		{
			return mesh_weak_ptr_.lock();
		}

		return MeshPtr();
	}

	// 得到网格的面数
	uint32_t SubMesh::GetFaceCount()
	{
		return index_buffer_.index_count() / 3;
	}

	RenderOperation SubMesh::GetRenderOperation()
	{
		return RenderOperation(RenderOperation::OT_TRIANGLE_LIST,vao_);
	}
}