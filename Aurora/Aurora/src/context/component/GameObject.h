#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <unordered_map>
#include <typeinfo>
#include <memory>

#include "AuroraDef.h"
#include "IComponent.h"
#include "TypeTraits.h"

namespace aurora
{
	/*
	* ����ʵ��,���ڳ������;
	* �������֮��Ľ���;
	*/
	class GameObject :public std::enable_shared_from_this<GameObject>
	{
	public:
		static uint64_t s_global_game_id;

		friend class GameObjectFactory;

		GameObject();
		~GameObject();

		// ��ֹ����
		GameObject(const GameObject&) = delete;
		const GameObject& operator=(const GameObject&) = delete;

		/*
		* �������͵õ���Ӧ�����;
		*/
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			auto component = GetComponent(COMPONENT_ID(T));
			if (component)
			{
				return std::dynamic_pointer_cast<T>(component);
			}

			return std::shared_ptr<T>();
		}

		/*
		* ��������ɾ�����;
		*/
		template<class T>
		void RemoveComponent()
		{
			auto iter = id_by_component_map_.find(COMPONENT_ID(T));
			if (iter != id_by_component_map_.end()) {
				return;
			}

			iter->second->Dispose();
			id_by_component_map_.erase(iter);
		}

		/*
		 * ��������������;
		 */
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			auto iter = id_by_component_map_.find(COMPONENT_ID(T));
			if (iter != id_by_component_map_.end()) {
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			std::shared_ptr<T> component = std::make_shared<T>();
			if (component) {
				component->AttackGameObject(shared_from_this());
				component->Start();
				id_by_component_map_.insert(std::make_pair(COMPONENT_ID(T), component));
			}
			return component;
		}
		/*
		 * ÿ֡����
		 */
		void Update();

		void set_name(const std::string& name) { name_ = name; }
		const std::string& name() const { return name_; }
	private:
		
	private:
		/*
		 * ��������������;
		 */
		template<class T>
		std::shared_ptr<T> AddComponent(const std::shared_ptr<T>& origin_component)
		{
			auto iter = id_by_component_map_.find(origin_component->GetComponentId());
			if (iter != id_by_component_map_.end()) {
				return iter->second;
			}

			auto component = origin_component->Clone();
			//auto component = std::shared_ptr<typename TypeTraits<decltype(*raw_origin_component)>::Type>(std::move(raw_origin_component));
			if (component)
			{
				origin_component->Copy(component);

				component->AttackGameObject(shared_from_this());
				component->Start();
				id_by_component_map_.insert(std::make_pair(component->GetComponentId(), component));
			}

			return component;
		}

		IComponentPtr GetComponent(const std::string& id);

		std::string name_;
		std::unordered_map<std::string, IComponentPtr> id_by_component_map_;
	};

}

#endif