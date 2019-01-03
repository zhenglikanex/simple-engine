#ifndef MESH_RENDERABLE_H_
#define MESH_RENDERABLE_H_

#include <vector>

#include "IRenderer.h"
#include "AuroraDef.h"
#include "Material.h"
#include "Mesh.h"

namespace aurora
{
	class MeshRenderer : public IRenderer
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();

	/*************************IComponent*************************/
		void Start() override;
		void Update() override;
		void Dispose() override;

		ComponentID GetComponentId() override;
		IComponentPtr Clone() override;
	private:
		void Copy(const IComponentPtr& component) override;

	/*************************IRenderer*************************/
	public:
		const AABB& GetBoundingBox() const override;

	/*************************MeshRenderer*************************/
	public:
		void set_mesh(const MeshPtr& mesh) { mesh_ = mesh; }
		const MeshPtr& mesh() const { return mesh_; }
	private:
		MeshPtr mesh_;
	};
}

#endif
