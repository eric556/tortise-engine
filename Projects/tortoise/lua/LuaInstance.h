#pragma once
#include <sol.hpp>
#include "../ecs/Entity.hpp"
#include "../ecs/EntityManager.hpp"

namespace tortoise {
	namespace lua {
		class LuaInstance {
		public:
			template<class T>
			sol::usertype<T> registerComponent(std::string name) {
				// create the new type
				sol::usertype <T> type = MainState.new_usertype<T>(name);

				// create a method so it can be added to and removed from entities
				MainState["Entity"]["add" + name] = &ECS::Entity::addComponent<T>;
				MainState["Entity"]["remove" + name] = &ECS::Entity::removeComp<T>;
				MainState["Entity"]["get" + name] = &ECS::Entity::getComponent<T>;
				return type;
			}

			void Init(std::string assetsPath);

			sol::state_view getStateView();
			void resetState();

		private:
			sol::state MainState;
		};
	}
}