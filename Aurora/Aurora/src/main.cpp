#include <iostream>
#include <fstream>
#include <sstream>

#include "StringUtil.h"
#include "AuroraDef.h"
#include "Config.h"
#include "App3D.h"
#include "Clock.h"
#include "Resources.h"
#include "FileHelper.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "SceneNode.h"
#include "GameObjectFactory.h"
#include "Context.h"
#include "PointLight.h"

using namespace aurora;

class Test1
{
public:
	using Type = Test1;
};

class Test2 : public Test1
{
public:
	using Type = Test2;
};

struct UnkownValue
{
	void* ptr;
	size_t size;
};

using NameByUniformMap = std::unordered_map<std::string, UnkownValue>;

class TestApp : public App3D
{
public:
	bool OnCreate() override
	{
		/*MeshPtr mesh = MeshManager::GetInstance()->LoadRes("test");
		MaterialPtr mat_ptr = MaterialManager::GetInstance()->LoadRes("test");
		FileHelper::GetInstance()->AddSearchPath("/../Asset/");*/
		//auto file_identifer = FileHelper::GetInstance()->OpenFileIdentifer("aurora.config");

		//auto game_object = GameObjectFactory::GetInstance()->CreateGameObject(GameObjectFactory::s_kNodeGameObject);

		//NameByUniformMap map;

		//FileHelper::GetInstance()->AddSearchPath("/../Asset/");

		//auto mesh = LoadMesh("model/nanosuit.obj");

		//auto game_object = CREATE_GAMEOBJECT(GameObjectFactory::s_kMeshGameObject);
		//game_object->GetComponent<MeshRenderer>()->set_mesh(mesh);
		////game_object->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 0, -20));
		////game_object->GetComponent<SceneNode>()->set_scale(glm::vec3(0.5, 0.5, 0.5));

		//Context::GetInstance()->scene_manager().AddToRootNode(game_object);

		auto camera_obj = CREATE_GAMEOBJECT(GameObjectFactory::s_kCameraGameObject);
		Context::GetInstance()->scene_manager().AddToRootNode(camera_obj);

		//camera_obj->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 0, 80));

		//auto point_light_obj = CREATE_GAMEOBJECT(GameObjectFactory::s_kPointLight);
		//Context::GetInstance()->scene_manager().AddToRootNode(point_light_obj);
		//
		//point_light_obj->GetComponent<SceneNode>()->set_local_position(glm::vec3(5, 0, 0));

		//auto point_light = point_light_obj->GetComponent<PointLight>();
		//point_light->set_color(glm::vec3(1.0f, 0.0f, 0.0f));

		return true;
	}

	void OnDestory() override
	{
		
	}

	void OnUpdate() override
	{
		//std::cout << fps() << std::endl;
	}
private:
};

int main()
{
	std::shared_ptr<App3D> app = std::make_shared<TestApp>();
	if (app->Create())
	{
		app->set_fps_interval(1.0f / 60.0f);
		app->Run();
	}

	system("pause");
	return 0;
}