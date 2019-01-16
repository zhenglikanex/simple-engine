#include "GameObjectFactory.h"

#include "GameObject.h"
#include "SceneNode.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "PointLight.h"
#include "DirectionalLight.h"

namespace aurora
{
	const std::string GameObjectFactory::s_kEmptyGameObject = "EmptyGameOject";
	const std::string GameObjectFactory::s_kNodeGameObject = "NodeGameObject";
	const std::string GameObjectFactory::s_kRenderableGameObject = "RenderableGameObject";
	const std::string GameObjectFactory::s_kCameraGameObject = "CameraGameObject";
	const std::string GameObjectFactory::s_kMeshGameObject = "MeshGameObject";
	const std::string GameObjectFactory::s_kPointLight = "PointLightGameObject";
	const std::string GameObjectFactory::s_kDirectionalLight = "DirectionalLight";

	GameObjectFactory::GameObjectFactory()
	{
		
	}

	GameObjectFactory::~GameObjectFactory()
	{
		
	}

	bool GameObjectFactory::Initialize()
	{
		// 预先注册的gameobject对象
		RegisterPerfab(s_kEmptyGameObject, MakeGameObjectPtr());
		
		auto node_game_object = MakeGameObjectPtr();
		node_game_object->AddComponent<SceneNode>();
		RegisterPerfab(s_kNodeGameObject, std::move(node_game_object));

		auto camera_game_object = MakeGameObjectPtr();
		camera_game_object->AddComponent<SceneNode>();
		camera_game_object->AddComponent<Camera>();
		RegisterPerfab(s_kCameraGameObject, std::move(camera_game_object));

		auto mesh_game_object = MakeGameObjectPtr();
		mesh_game_object->AddComponent<SceneNode>();
		mesh_game_object->AddComponent<MeshRenderer>();
		RegisterPerfab(s_kMeshGameObject, std::move(mesh_game_object));

		auto point_light = MakeGameObjectPtr();
		point_light->AddComponent<SceneNode>();
		point_light->AddComponent<PointLight>();
		RegisterPerfab(s_kPointLight, std::move(point_light));

		auto directional_light = MakeGameObjectPtr();
		directional_light->AddComponent<SceneNode>();
		directional_light->AddComponent<DirectionalLight>();
		RegisterPerfab(s_kDirectionalLight, std::move(directional_light));

		return true;
	}

	void GameObjectFactory::RegisterPerfab(const std::string& id,GameObjectPtr&& game_object)
	{
		auto iter = id_by_perfab_map_.find(id);
		if (iter != id_by_perfab_map_.end())
		{
			return;
		}

		GameObjectPtr perfab;
		perfab.swap(game_object);

		id_by_perfab_map_.insert(std::make_pair(id,std::move(perfab)));
	}

	void GameObjectFactory::RemovePerfab(const std::string& id)
	{
		id_by_perfab_map_.erase(id);
	}

	GameObjectPtr GameObjectFactory::CreateGameObject(const std::string& id)
	{
		auto iter = id_by_perfab_map_.find(id);
		if (iter != id_by_perfab_map_.end())
		{
			return CreateGameObject(iter->second);
		}

		return GameObjectPtr();
	}

	GameObjectPtr GameObjectFactory::CreateGameObject(const GameObjectPtr& origin_game_object)
	{
		auto game_object = MakeGameObjectPtr();
		for (auto& iter : origin_game_object->id_by_component_map_)
		{
			// 拷贝添加
			auto component = game_object->AddComponent(iter.second);
		}

		return game_object;
	}
}