#pragma once
#include <ecs/Component.hpp>
#include <SFML/Graphics.hpp>

namespace Components {
	class BoundingBox : public tortoise::ecs::Component {
	public:
		BoundingBox();
		void debug();
		std::string dump(std::string name);

	public:
		sf::FloatRect boundingBox;
		bool display;
	private:
		float boundingBoxPos[2] = { 0.f, 0.f };
		float boundingBoxSize[2] = { 0.f, 0.f };
	};
}