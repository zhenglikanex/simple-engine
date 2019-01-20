#include "Mesh.h"

#include <cassert>

namespace aurora
{
	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{

	}

	void Mesh::AddSubMesh(const SubMeshPtr& submesh_ptr)
	{
		submeshs_.push_back(submesh_ptr);
	}

	const SubMeshPtr& Mesh::GetSubMesh(size_t index) const
	{
		assert(index >= 0 && index < submeshs_.size());

		return submeshs_[index];
	}
}