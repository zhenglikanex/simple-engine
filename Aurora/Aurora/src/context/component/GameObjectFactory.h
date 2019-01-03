#ifndef GAMEOBJECT_FACTORY_H_
#define GAMEOBJECT_FACTORY_H_

#include <string>
#include <unordered_map>

#include "AuroraDef.h"
#include "Singleton.h"

#define CREATE_GAMEOBJECT(id) GameObjectFactory::GetInstance()->CreateGameObject(id)
#define CLONE_GAMEOBJECT(game_object) GameObjectFactory::GetInstance()->CreateGameObject(game_object)

namespace aurora
{
	class GameObjectFactory : public Singleton<GameObjectFactory>
	{
	public:
		const static std::string s_kEmptyGameObject;
		const static std::string s_kNodeGameObject;
		const static std::string s_kRenderableGameObject;
		const static std::string s_kCameraGameObject;
		const static std::string s_kMeshGameObject;
		const static std::string s_kPointLight;
	public:
		GameObjectFactory();
		~GameObjectFactory();

		bool Initialize() override;

		void RegisterPerfab(const std::string& id,GameObjectPtr&& game_object);
		void RemovePerfab(const std::string& id);

		GameObjectPtr CreateGameObject(const std::string& id);
		GameObjectPtr CreateGameObject(const GameObjectPtr& origin_game_object);
	private:
		// GameObjectµÄÔ¤ÖÆ
		std::unordered_map<std::string, GameObjectPtr> id_by_perfab_map_;
	};
}

#endif
