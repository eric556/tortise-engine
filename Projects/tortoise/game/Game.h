#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../lua/LuaInstance.h"
#include "../ecs/EntityManager.hpp"
#include "../resources/ResourceManager.h"


namespace tortoise {
	namespace game {
		class Game {
		public:
			Game(std::string name, unsigned int width, unsigned int height, std::string assetPath);
			void Start(std::string filepath);
			lua::LuaInstance lua;
			ecs::EntityManager eManager;
			sf::RenderWindow window;
			asset::ResourceManager rManager;
			bool running;
		protected:
			void Start();
			sol::function_result Load(std::string filepath);
			virtual void registerLua() = 0;
			sf::Clock deltaClock;
		};
	}
}