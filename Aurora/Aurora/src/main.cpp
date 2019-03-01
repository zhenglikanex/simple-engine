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
#include "DirectionalLight.h"
#include "SubMesh.h"
#include "Texture.h"

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

		FileHelper::GetInstance()->AddSearchPath("/../Asset/");

		auto mesh = LoadMesh("model/nanosuit.obj");

		auto game_object = CREATE_GAMEOBJECT(GameObjectFactory::s_kMeshGameObject);
		game_object->set_name("nanosuit");
		game_object->GetComponent<MeshRenderer>()->set_mesh(mesh);
		game_object->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 0, -10));
		game_object->GetComponent<SceneNode>()->set_scale(glm::vec3(2.0, 2.0, 2.0));

		Context::GetInstance()->scene_manager()->AddToRootNode(game_object);

		auto camera_obj = CREATE_GAMEOBJECT(GameObjectFactory::s_kCameraGameObject);
		Context::GetInstance()->scene_manager()->AddToRootNode(camera_obj);

		auto dl_obj = CREATE_GAMEOBJECT(GameObjectFactory::s_kDirectionalLight);
		dl_obj->GetComponent<DirectionalLight>()->set_color(glm::vec3(1.f, 1.0f, 1.0f));
		dl_obj->GetComponent<DirectionalLight>()->set_dir(glm::vec3(-2, -5, -10));
		Context::GetInstance()->scene_manager()->AddToRootNode(dl_obj);

		/*auto dl_obj1 = CREATE_GAMEOBJECT(GameObjectFactory::s_kDirectionalLight);
		dl_obj1->GetComponent<DirectionalLight>()->set_color(glm::vec3(1.f, 1.0f, 1.0f));
		dl_obj1->GetComponent<DirectionalLight>()->set_dir(glm::vec3(2, -5, -10));
		Context::GetInstance()->scene_manager()->AddToRootNode(dl_obj1);*/

		auto plane = CREATE_GAMEOBJECT(GameObjectFactory::s_kPlane);
		plane->set_name("plane");
		plane->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 5, -10));
		plane->GetComponent<SceneNode>()->set_scale(glm::vec3(20));
		plane->GetComponent<SceneNode>()->set_rotate(glm::vec3(50, 0, 0));
		Context::GetInstance()->scene_manager()->AddToRootNode(plane);

		auto material = plane->GetComponent<MeshRenderer>()->mesh()->GetSubMesh(0)->material_ptr();
		auto texture = LoadTexture2D("model/timg.jpg");
		material->AttachTexture("tex_diffuse",texture);
		

		camera_obj->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 0, 20));

		glm::vec3 pos(1.0, 2.0, 1.0);
		auto mat = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(1.0));
		auto mat2 = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0,1.0,0.0));

		auto point_light_obj = CREATE_GAMEOBJECT(GameObjectFactory::s_kPointLight);
		Context::GetInstance()->scene_manager()->AddToRootNode(point_light_obj);

		point_light_obj->GetComponent<SceneNode>()->set_local_position(glm::vec3(0, 10, 0));

		auto point_light = point_light_obj->GetComponent<PointLight>();
		point_light->set_color(glm::vec3(1.0f, 0.0f, 0.0f));
		point_light->set_intensity(2.0f);

		glm::vec3 front(0.0, -1.0, 0.0);
		glm::vec3 up(0.0, 1.0, 0.0);
		glm::vec3 right = glm::normalize(glm::cross(glm::normalize(front), up));
		up = glm::normalize(glm::cross(up, front));

		glm::mat4 m = glm::lookAt(glm::vec3(0.f), glm::vec3(0.0f, -1.0f, 0.0f), up);

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