#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

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

		void set_dir(const glm::vec3& dir) { dir_ = dir; }
		const glm::vec3 dir() const { return dir_; }

	protected:
		void Copy(const IComponentPtr& component) override;
	private:
		glm::vec3 dir_;
	};
}

#endif
