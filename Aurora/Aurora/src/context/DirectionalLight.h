#ifndef POINT_LIGHT_H_
#define POINT_LIGHT_H_

#include "AuroraDef.h"
#include "Light.h"

namespace aurora
{
	class DirectionalLight : public Light
	{
	public:
		DirectionalLight();
		~DirectionalLight();

		ComponentID GetComponentId() override;
		IComponentPtr Clone() override;

		void Update() override;
	protected:
		void Copy(const IComponentPtr& component) override;
	};
}

#endif
