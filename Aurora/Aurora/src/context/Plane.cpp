#include "Plane.h"
#include "VertexLayout.h"
#include "SubMesh.h"
#include "Mesh.h"
#include "Material.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "AuroraDef.h"

namespace aurora
{
	Plane::Plane()
		: row_count_(1)
		, col_count_(1)
	{

	}

	Plane::~Plane()
	{
	}

	ComponentID Plane::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	void Plane::Start()
	{
		UpdateMesh();
	}

	void Plane::UpdateMesh()
	{
		std::vector<Vertex_P3FN3FT2F> vertices;
		std::vector<uint32_t> indexs;

		uint32_t row_line_count = row_count_ + 1;
		uint32_t col_line_count = col_count_ + 1;

		float row_step = (1.0f / row_count_);
		float col_step = (1.0f / col_count_);

		Vertex_P3FN3FT2F vertex;
		for (uint32_t row = 0; row <= row_count_; ++row)
		{
			for (uint32_t col = 0; col <= col_count_; ++col)
			{
				vertex.position = glm::vec3(-0.5 + col * col_step, 0, -0.5 + row_step * row);
				vertex.normal = glm::vec3(0, 1, 0);
				vertex.texcoords = glm::vec2(col*col_step, row_step * row);

				vertices.push_back(vertex);
			}
		}

		// 按正方形来插入顶点索引
		for (uint32_t row = 0; row < row_count_; ++row)
		{
			for (uint32_t col = 0; col < col_count_; ++col)
			{
				uint32_t begin_index = row * col_line_count + col;

				indexs.push_back(begin_index);
				indexs.push_back(begin_index + 1);
				indexs.push_back(begin_index + col_line_count);

				indexs.push_back(begin_index + 1);
				indexs.push_back(begin_index + col_line_count + 1);
				indexs.push_back(begin_index + col_line_count);
			}
		}

		auto sub_mesh = MakeSubMeshPtr(
			MakeVertexBufferPtr(VertexLayout::kP3FN3FT2F, vertices.size(), (uint8_t*)vertices.data()),
			MakeIndexBufferPtr(IndexLayout::k32Bit, indexs.size(), (uint8_t*)indexs.data()),
			Resources::s_kSimpleMtl->Clone());

		auto mesh = MakeMeshPtr();
		mesh->AddSubMesh(sub_mesh);

		auto mesh_renderer = AddComponent<MeshRenderer>();
		if (mesh_renderer)
		{
			mesh_renderer->set_mesh(mesh);
		}
	}

	IComponentPtr Plane::Clone()
	{
		return MakePlanePtr();
	}

	void Plane::Copy(const IComponentPtr& component)
	{
		auto plane = std::dynamic_pointer_cast<Plane>(component);
		if (plane)
		{
			row_count_ = plane->row_count_;
			col_count_ = plane->col_count_;
		}
	}
}
