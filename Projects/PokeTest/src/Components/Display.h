#pragma once
#include <string>
#include <ecs/Component.hpp>
#include <SFML/Graphics.hpp>


namespace Components {
	class Display : public tortoise::ecs::Component {
	public:
		Display();
		void debug();
		std::string dump(std::string name);
	public:
		sf::RectangleShape shape;

	private:
		float color[3] = { 0.f, 0.f, 0.f };
		float size[2] = { 0.0f, 0.0f };
		float origin[2] = { 0.0f, 0.0f };
	};
}
