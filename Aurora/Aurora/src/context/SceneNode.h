#ifndef NODE_COMPONENT_H_
#define NODE_COMPONENT_H_

#include <string>
#include <vector>
#include <memory>

#include "AuroraDef.h"
#include "IComponent.h"

#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	class SceneNode : public IComponent , public std::enable_shared_from_this<SceneNode>
	{
	public:
		SceneNode();
		~SceneNode();

		void Start() override;
		void Update() override;
		void Dispose() override;

		ComponentID GetComponentId() override;
	public:
		void AddChild(const GameObjectPtr& game_object);
		void AddChild(const SceneNodePtr& node);
		SceneNodePtr FindByName(const std::string& name) const;
		SceneNodePtr Find(const std::string& name) const;

		SceneNodePtr GetParent() const;
		std::vector<SceneNodePtr> GetChildren() const;

		glm::mat4 GetWorldMatrix();

		void set_position(const glm::vec3& position)
		{
			if (position == position_)
			{
				return;
			}

			position_ = position;
			
			auto parent = GetParent();
			if (parent)
			{
				local_position_ = glm::inverse(parent->GetWorldMatrix()) * glm::vec4(position_, 1.0f);
			}
			else
			{
				local_position_ = position_;
			}
			
			need_update_matrix_ = true;
			UpdateTransformMatrix();
		}
		const glm::vec3& position() const
		{
			return position_;
		}

		void set_local_position(const glm::vec3& local_position) 
		{
			if (local_position == local_position_)
			{
				return;
			}

			local_position_ = local_position;
			auto parent = GetParent();
			if (parent)
			{
				position_ = parent->GetWorldMatrix() * glm::vec4(local_position_, 1.0f);
			}
			else
			{
				position_ = local_position_;
			}

			need_update_matrix_ = true;
			UpdateTransformMatrix();
		}
		const glm::vec3& local_position() const { return local_position_; }

		void set_scale(const glm::vec3& scale) 
		{ 
			if (scale == scale_)
			{
				return;
			}

			scale_ = scale; 

			need_update_matrix_ = true;
			UpdateTransformMatrix();
		}
		const glm::vec3& scale() const { return scale_; }
		
		void set_rotate(const glm::vec3& rotate)
		{
			if (rotate == rotate_)
			{
				return;
			}

			rotate_ = rotate;

			need_update_matrix_ = true;
			UpdateTransformMatrix();
		}
		const glm::vec3& rotate() const { return rotate_; }

		const glm::mat4x4& transform_matrix() const { return transform_matrix_; }
	private:
		void UpdateTransformMatrix();
		void Copy(const IComponentPtr& component) override;
		IComponentPtr Clone() override;
	private:
		glm::vec3 position_;
		glm::vec3 local_position_;
		glm::vec3 scale_;
		glm::vec3 rotate_;
		bool need_update_matrix_;
		glm::mat4x4 transform_matrix_;
		GameObjectWeakPtr parent_;
		std::vector<GameObjectPtr> children_;
	};
}

#endif
