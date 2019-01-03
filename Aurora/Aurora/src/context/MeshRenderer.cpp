#include "MeshRenderer.h"

#include "Context.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SubMesh.h"
#include "RenderObject.h"

namespace aurora
{
	MeshRenderer::MeshRenderer()
	{

	}

	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::Start()
	{

	}

	void MeshRenderer::Update()
	{
		if (!mesh_)
		{
			return;
		}

		auto cameras = Context::GetInstance()->scene_manager().cameras();
		for (auto& camera : cameras)
		{
			// 判断layer对摄像机是否可见
			if (camera->CheckVisibleLayer(layer_id()))
			{
				for (auto& submesh : mesh_->submeshs())
				{
					auto iter = camera->render_group_map().find(RenderOperation::OT_TRIANGLE_LIST);
					if (iter != camera->render_group_map().end())
					{
						auto scene_node = GetComponent<SceneNode>();
						RenderObject render_object(scene_node->GetWorldMatrix(),submesh->material_ptr(), submesh->GetRenderOperation());

						auto render_queue_iter = iter->second.get(submesh->material_ptr());
						render_queue_iter->second.push_back(render_object);
					}
				}
			}
		}
	}

	void MeshRenderer::Dispose()
	{

	}

	ComponentID MeshRenderer::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	void MeshRenderer::Copy(const IComponentPtr& component)
	{
		IRenderer::Copy(component);
	}

	IComponentPtr MeshRenderer::Clone()
	{
		auto mesh_renderer = MakeMeshRendererPtr();
		return mesh_renderer;
	}

	const AABB& MeshRenderer::GetBoundingBox() const
	{
		return boundingbox_;
	}
}