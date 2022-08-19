#pragma once
#include <string>
#include <ecs/Component.hpp>
#include <SFML/Graphics.hpp>

namespace Components {
	class Input : public tortoise::ecs::Component {
	public:
		Input();
		void debug();
		std::string dump(std::string name);
	public:
		float speed;
	};
}