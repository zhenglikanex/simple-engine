#include "SceneNode.h"

#include "StringUtil.h"
#include "GameObject.h"

#include "glm/gtc/matrix_transform.hpp"

namespace aurora
{
	SceneNode::SceneNode()
		: position_(0, 0, 0)
		, local_position_(0, 0, 0)
		, scale_(1, 1, 1)
		, rotate_(0, 0, 0)
		,transform_matrix_(glm::identity<glm::mat4>())
		,need_update_matrix_(false)
	{

	}

	SceneNode::~SceneNode()
	{

	}

	void SceneNode::Start()
	{
		
	}

	void SceneNode::Update()
	{

	}

	void SceneNode::Dispose()
	{
		
	}

	ComponentID SceneNode::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	void SceneNode::AddChild(const GameObjectPtr& game_object)
	{
		auto scene_node = game_object->GetComponent<SceneNode>();
		if (scene_node)
		{
			scene_node->parent_ = shared_from_this()->GetGameObject();
			children_.emplace_back(game_object);
		}
	}

	void SceneNode::AddChild(const SceneNodePtr& node)
	{
		auto game_object = node->GetGameObject();
		if (game_object)
		{
			node->parent_ = shared_from_this()->GetGameObject();
			children_.emplace_back(std::move(game_object));
		}
	}

	SceneNodePtr SceneNode::FindByName(const std::string& name) const
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
			{
				return child->GetComponent<SceneNode>();
			}
		}

		return SceneNodePtr();
	}

	SceneNodePtr SceneNode::Find(const std::string& name) const
	{
		auto child_names = StringUtil::split(name, '/');
		if (child_names.size() <= 0)
		{
			return SceneNodePtr();
		}

		auto current_node = FindByName(child_names[0]);
		if (current_node)
		{
			for (int i = 1; i < child_names.size(); ++i)
			{
				current_node = current_node->FindByName(child_names[i]);
				if (!current_node)
				{
					return SceneNodePtr();
				}
			}
		}

		return current_node;
	}

	SceneNodePtr SceneNode::GetParent() const
	{
		auto parent_game_object = parent_.lock();
		if (!parent_game_object)
		{
			return SceneNodePtr();
		}
		return parent_game_object->GetComponent<SceneNode>();
	}

	std::vector<SceneNodePtr> SceneNode::GetChildren() const
	{
		std::vector<SceneNodePtr> nodes;
		for (auto& child : children_)
		{
			nodes.emplace_back(child->GetComponent<SceneNode>());
		}

		return std::move(nodes);
	}

	glm::mat4 SceneNode::GetWorldMatrix()
	{
		auto parent = GetParent();
		if (parent)
		{
			return parent->transform_matrix() * transform_matrix_;
		}
		else
		{
			return glm::identity<glm::mat4>() * transform_matrix_;
		}
	}

	void SceneNode::UpdateTransformMatrix()
	{
		if (need_update_matrix_)
		{
			
			transform_matrix_ = glm::translate(glm::identity<glm::mat4>(), local_position_);
			transform_matrix_ = glm::rotate(transform_matrix_, glm::radians(rotate_.x), glm::vec3(1, 0, 0));
			transform_matrix_ = glm::rotate(transform_matrix_, glm::radians(rotate_.y), glm::vec3(0, 1, 0));
			transform_matrix_ = glm::rotate(transform_matrix_, glm::radians(rotate_.z), glm::vec3(0, 0, 1));
			transform_matrix_ = glm::scale(transform_matrix_, scale_);

			need_update_matrix_ = false;
		}
	}

	void SceneNode::Copy(const IComponentPtr& component)
	{
		IComponent::Copy(component);

		auto scene_node = std::dynamic_pointer_cast<SceneNode>(component);
		if (scene_node)
		{
			scene_node->position_ = position_;
			scene_node->local_position_ = local_position_;
			scene_node->scale_ = scale_;
		}
	}

	IComponentPtr SceneNode::Clone()
	{
		auto scene_node = MakeSceneNodePtr();
		return scene_node;
	}
}