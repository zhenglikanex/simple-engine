#include "DirectionalLight.h"
#include "SceneNode.h"
#include "LightSystem.h"
#include "GameObject.h"

namespace aurora
{
	DirectionalLight::DirectionalLight()
		: Light(LightType::kDirectionalLight)
		,dir_(0,-1.0,0.0)
	{

	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Update()
	{
		DirectionalLightParameter light_param;
		light_param.position = GetComponent<SceneNode>()->position();
		light_param.directional = dir_;
		light_param.color = color_;
		light_param.intensity = intensity_;

		LightSystem::GetInstance()->PushDirectionalLight(light_param);
	}

	ComponentID DirectionalLight::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	IComponentPtr DirectionalLight::Clone()
	{
		return MakeDirectionalLightPtr();
	}

	void DirectionalLight::Copy(const IComponentPtr& component)
	{
		auto dir_light = std::dynamic_pointer_cast<DirectionalLight>(component);
		if (dir_light)
		{
			Light::Copy(dir_light);

			dir_light->dir_ = dir_;
		}
	}
}