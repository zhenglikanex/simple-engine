#include "LightSystem.h"

namespace aurora
{
	LightSystem::LightSystem()
	{

	}

	LightSystem::~LightSystem()
	{

	}

	void LightSystem::clear()
	{
		point_lights_.clear();
		directional_lights_.clear();
		spot_lights_.clear();
	}

	bool LightSystem::IsMaxLight()
	{
		if (point_lights_.size() + directional_lights_.size() + spot_lights_.size() >= s_kMaxLightCount)
		{
			return true;
		}

		return false;
	}

	void LightSystem::PushPointLight(const PointLightParameter& point_light_param)
	{
		if (IsMaxLight())
		{
			return;
		}

		point_lights_.emplace_back(point_light_param);
	}

	void LightSystem::PushDirectionalLight(const DirectionalLightParameter& dir_light_param)
	{
		if (IsMaxLight())
		{
			return;
		}

		directional_lights_.emplace_back(dir_light_param);
	}

	void LightSystem::PushSpotLight(const SpotLightParameter& spot_light_param)
	{
		if (IsMaxLight())
		{
			return;
		}

		spot_lights_.emplace_back(spot_light_param);
	}
}