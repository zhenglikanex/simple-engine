#ifndef SUBMESH_H_
#define SUBMESH_H_

#include "VertexLayout.h"
#include "AuroraDef.h"
#include "RenderOperation.h"

namespace aurora
{
	class SubMesh
	{
	public:
		SubMesh(const MeshPtr& mesh_ptr,VertexBuffer&& vertex_buffer, IndexBuffer&& index_buffer);
		SubMesh(const MeshPtr& mesh_ptr, VertexBuffer&& vertex_buffer, IndexBuffer&& index_buffer,const MaterialPtr& material_ptr);
		~SubMesh();

		MeshPtr GetMesh();

		// 得到网格的面数
		uint32_t GetFaceCount();

		RenderOperation GetRenderOperation();

		const VertexBuffer& vertex_buffer() const { return vertex_buffer_; }
		const IndexBuffer& index_buffer() const { return index_buffer_; }

		void set_material_ptr(const MaterialPtr& material_ptr) { material_ptr_ = material_ptr; }
		const MaterialPtr& material_ptr() const { return material_ptr_; }
	private:
		MeshWeakPtr mesh_weak_ptr_;
		
		VertexBuffer vertex_buffer_;
		IndexBuffer index_buffer_;
		VertexArrayObject vao_;
		MaterialPtr material_ptr_;
	};
}

#endif
