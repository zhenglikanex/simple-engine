#ifndef LIGHT_SYSTEM_H_
#define LIGHT_SYSTEM_H_

#include <vector>

#include "AuroraDef.h"
#include "Singleton.h"

#include "glm/glm.hpp"

namespace aurora
{
	struct PointLightParameter
	{
		glm::vec3 position;
		glm::vec3 color;
		float intensity;
		float radius;
		float constant;     //kc
		float linear;       //kl
		float quadratic;    //kq
	};

	struct DirectionalLightParameter
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 directional;
		float intensity;
	};

	struct SpotLightParameter
	{
		
	};

	// 用来处理场景的灯光
	class LightSystem : public Singleton<LightSystem>
	{
	public:
		using PointLightVec = std::vector<PointLightParameter>;
		using DirectionalLightVec = std::vector<DirectionalLightParameter>;
		using SpotLightVec = std::vector<SpotLightParameter>;

		const static uint32_t s_kMaxLightCount = 16;

		LightSystem();
		~LightSystem();

		void clear();

		bool IsMaxLight();

		void PushPointLight(const PointLightParameter& point_light_param);
		void PushDirectionalLight(const DirectionalLightParameter& dir_light_param);
		void PushSpotLight(const SpotLightParameter& spot_light_param);

		const PointLightVec& point_lights() const { return point_lights_; }
		const DirectionalLightVec& directional_lights() const { return directional_lights_; }
		const SpotLightVec& spot_lights() const { return spot_lights_; }
	private:
		PointLightVec point_lights_;
		DirectionalLightVec directional_lights_;
		SpotLightVec spot_lights_;

	};
}

#endif
