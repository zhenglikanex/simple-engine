#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "AuroraDef.h"
#include "Light.h"

namespace aurora
{
	class PointLight : public Light
	{
	public:
		PointLight();
		~PointLight();

		ComponentID GetComponentId() override;
		IComponentPtr Clone() override;

		void Update() override;

		void set_radius(float radius) { radius_ = radius; }
		void set_constant(float constant) { constant_ = constant; }
		void linear(float linear) { linear_ = linear; }
		void quadratic(float quadratic) { quadratic_ = quadratic; }

		float constant() const { return constant_; }
		float linear() const { return linear_; }
		float quadratic() const { return quadratic_; }

	protected:
		void Copy(const IComponentPtr& component) override;
	private:
		float radius_;

		// Ë¥¼õ¹«Ê½ attenuation = 1.0/(kc + kl * d + kq * d^2)
		float constant_;     //kc
		float linear_;       //kl
		float quadratic_;    //kq
	};
}

#endif
