#include "Light.h"

namespace aurora
{
	Light::Light(LightType light_type) 
		: light_type_(light_type)
		, color_(1.0f, 1.0f, 1.0f)
		, intensity_(1.0f) 
	{
	}

	Light::~Light()
	{
	}

	void Light::Copy(const IComponentPtr& component)
	{
		auto light = std::dynamic_pointer_cast<Light>(component);
		if (light)
		{
			light->light_type_ = light_type_;
			light->color_ = color_;
			light->intensity_ = intensity_;
		}
	}
}