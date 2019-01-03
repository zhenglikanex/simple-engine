#ifndef ICOMPONENT_H_
#define ICOMPONENT_H_

#define COMPONENT_ID(Type) typeid(Type).name()

#include <string>
#include <memory>

#include "AuroraDef.h"

namespace aurora
{
	using ComponentID = std::string;

	/*
	* 组件接口;
	*/
	class IComponent
	{
	public:
		friend class GameObject;

		virtual ~IComponent() = 0;

		virtual void Start() {};
		virtual void Update() {};
		virtual void Dispose() {};

		/*
		 * 得到组件所属的对象;
		 */
		GameObjectPtr GetGameObject();

		template<typename T>
		std::shared_ptr<T> GetComponent()
		{
			auto game_object = game_object_wake_ptr_.lock();
			if (game_object)
			{
				return game_object->GetComponent<T>();
			}

			return std::shared_ptr<T>();
		}

		template<typename T>
		void AddComponent()
		{
			auto game_object = game_object_wake_ptr_.lock();
			if (game_object)
			{
				return game_object->AddComponent<T>();
			}
		}

		/*
		 * 拷贝
		 */
		virtual ComponentID GetComponentId() = 0;

	protected:
		virtual void Copy(const IComponentPtr& component) = 0 {}
	public:
		void AttackGameObject(const GameObjectPtr& game_object);
		virtual std::shared_ptr<IComponent> Clone() = 0;

		GameObjectWeakPtr game_object_wake_ptr_;
	};
}

#endif