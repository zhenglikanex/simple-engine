#include "DirectionalLight.h"
#include "SceneNode.h"
#include "LightSystem.h"
#include "GameObject.h"

namespace aurora
{
	DirectionalLight::DirectionalLight()
		: Light(LightType::kDirectionalLight)
	{

	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Update()
	{
		DirectionalLightParameter light_param;
		light_param.position = GetComponent<SceneNode>()->position();
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
		auto point_light = std::dynamic_pointer_cast<DirectionalLight>(component);
		if (point_light)
		{
			Light::Copy(point_light);
		}
	}
}