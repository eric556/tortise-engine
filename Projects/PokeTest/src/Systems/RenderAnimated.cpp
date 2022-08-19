#include "RenderAnimated.h"
#include <ecs/EntityManager.hpp>
#include "../Components/Transform.h"
#include "../Components/AnimatedSprite.h"

using namespace tortoise;

void Systems::RenderAnimated::run(float dt, PokeGame* game)
{
	ecs::EntityManager eManager;
	auto displayEntities = eManager.getEntitiesByComponents<Components::AnimatedSprite, Components::Transform>();

	for (auto entity : displayEntities) {
		auto sprite = entity->getComponent<Components::AnimatedSprite>();
		auto transform = entity->getComponent<Components::Transform>();
		game->drawQueue.push({ (int)transform->position.z, [sprite, transform, dt](sf::RenderWindow& window, asset::ResourceManager& rManager) {
			auto text = rManager.getAsset<sf::Texture>(sprite->id);
			if (text != nullptr) {
				sprite->sprite.setTexture(*text);
				Components::Frame current = sprite->getCurrentFrame();
				sprite->sprite.setTextureRect(sf::IntRect(current.x, current.y, current.width, current.height));
				sprite->sprite.setPosition(std::floor(transform->position.x), std::floor(transform->position.y));
				sprite->sprite.setScale(transform->scale);
				window.draw(sprite->sprite);
				sprite->update(dt);
			}
		}});		
	}
}
