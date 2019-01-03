#include "SceneManager.h"

#include <algorithm>

#include "IRenderer.h"
#include "MeshRenderer.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include "LightSystem.h"

namespace aurora
{
	SceneManager::SceneManager()
	{
		root_node_ = CREATE_GAMEOBJECT(GameObjectFactory::s_kNodeGameObject);
		root_node_->GetComponent<SceneNode>()->set_local_position(glm::vec3(0.0, 0.0, 0.0));
	}

	SceneManager::~SceneManager()
	{
		
	}

	// 进行场景更新
	void SceneManager::Update()
	{
		LightSystem::GetInstance()->clear();

		cameras_.clear();

		auto camera_game_objects = Find<Camera>();
		for (auto& camera : camera_game_objects)
		{
			cameras_.push_back(camera->GetComponent<Camera>());
		}

		// 对Camera进行排序
		std::sort(cameras_.begin(), cameras_.end(), [](const CameraPtr& first, const CameraPtr& second)
		{
			return first->z_order() <= second->z_order();
		});

		Visit(root_node_->GetComponent<SceneNode>());
	}

	void SceneManager::AddToRootNode(const GameObjectPtr& game_object)
	{
		if (game_object)
		{
			root_node_->GetComponent<SceneNode>()->AddChild(game_object);
		}
	}

	GameObjectPtr SceneManager::Find(const std::string& name) const
	{
		auto node = root_node_->GetComponent<SceneNode>()->Find(name);
		if (node)
		{
			return node->GetGameObject();
		}

		return GameObjectPtr();
	}

	void SceneManager::Visit(const SceneNodePtr& scene_node)
	{
		scene_node->GetGameObject()->Update();

		// TODO：进行场景剔除
		for (auto& child_node : scene_node->GetChildren())
		{
			Visit(child_node);
		}
	}
}