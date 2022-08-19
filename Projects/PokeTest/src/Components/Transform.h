#pragma once
#include <ecs/Component.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <ecs/Entity.hpp>

namespace Components {
	class Transform : public tortoise::ecs::Component {
	public:
		Transform();
		void debug();
		std::string dump(std::string name);

		Transform getRelativeTo(std::shared_ptr<tortoise::ecs::Entity> entity);

	public:
		sf::Vector3f position;
		float rotation;
		sf::Vector2f scale;

	private:
		float position_array[3] = { 0.f, 0.f, 0.0f };
		float scale_array[2] = { 0.f, 0.f};

	};
}