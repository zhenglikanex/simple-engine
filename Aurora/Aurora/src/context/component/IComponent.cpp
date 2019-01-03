#include "IComponent.h"

#include <typeinfo>

#include "GameObject.h"

namespace aurora
{
	IComponent::~IComponent()
	{
	}

	ComponentID IComponent::GetComponentId()
	{
		return COMPONENT_ID(*this);
	}

	GameObjectPtr IComponent::GetGameObject()
	{
		return game_object_wake_ptr_.lock();
	}
	
	void IComponent::AttackGameObject(const GameObjectPtr& game_object)
	{
		game_object_wake_ptr_ = game_object;
	}
}

