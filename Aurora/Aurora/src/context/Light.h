#ifndef LIGHT_H_
#define LIGHT_H_

#include "AuroraDef.h"
#include "IComponent.h"

#include "glm/glm.hpp"

namespace aurora
{
	class Light : public IComponent
	{
	public:
		enum class LightType
		{
			kPointLight,		// 点光源
			kDirectionalLight,	// 方向光
			kSpotLight,			// 聚光灯
		};

		Light(LightType light_type);

		virtual ~Light() = 0;

	protected:
		void Copy(const IComponentPtr& component) override;

	public:
		void set_color(const glm::vec3& color) { color_ = color; }
		void set_intensity(float intensity) { intensity_ = intensity; }

		LightType light_type() const { return light_type_; }
		const glm::vec3& color() const { return color_; }
		float intensity() const { return intensity_; }
	protected:
		LightType light_type_;
		glm::vec3 color_;
		float intensity_;
	};
}

#endif
