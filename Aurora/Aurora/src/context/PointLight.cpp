#include "PointLight.h"
#include "SceneNode.h"
#include "LightSystem.h"
#include "GameObject.h"

namespace aurora
{
	PointLight::PointLight()
		: Light(LightType::kPointLight)
		, radius_(5)
		, constant_(1)
		, linear_(1)
		, quadratic_(1)
	{

	}

	PointLight::~PointLight()
	{

	}

	void PointLight::Update()
	{
		PointLightParameter light_param;
		light_param.position = GetComponent<SceneNode>()->position();
		light_param.color = color_;
		light_param.intensity = intensity_;
		light_param.radius = radius_;
		light_param.constant = constant_;
		light_param.linear = linear_;
		light_param.quadratic = quadratic_;

		LightSystem::GetInstance()->PushPointLight(light_param);
	}

	ComponentID PointLight::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	IComponentPtr PointLight::Clone()
	{
		return MakePointLightPtr();
	}

	void PointLight::Copy(const IComponentPtr& component)
	{
		auto point_light = std::dynamic_pointer_cast<PointLight>(component);
		if (point_light)
		{
			Light::Copy(point_light);
			
			point_light->radius_ = radius_;
			point_light->constant_ = constant_;
			point_light->linear_ = linear_;
			point_light->quadratic_ = quadratic_;
		}
	}
}