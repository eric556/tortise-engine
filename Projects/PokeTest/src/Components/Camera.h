#pragma once
#include <SFML/Graphics.hpp>
#include <ecs/Component.hpp>
#include <ecs/Entity.hpp>

namespace Components {
	class Camera : public tortoise::ecs::Component {
	public:
		Camera();
		void debug();
		std::string dump(std::string name);
	public:
		sf::View view;
		std::weak_ptr<tortoise::ecs::Entity> followEntity;
	private:
		float position[2] = { 0.f, 0.f };
		float size[2] = { 0.f, 0.f };
		float zoom = 1.0f;
	};
}