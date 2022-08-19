#include "RenderTilemapSystem.h"
#include <ecs/EntityManager.hpp>
#include "../Components/Transform.h"
#include "../Components/TileMap.h"
#include <memory>

using namespace tortoise;

void Systems::RenderTilemapSystem::run(PokeGame* game)
{
	ecs::EntityManager eManager;
	auto displayEntities = eManager.getEntitiesByComponents<Components::TileMap, Components::Transform>();

	for (auto entity : displayEntities) {
		auto transform = entity->getComponent<Components::Transform>();
		auto tilemap = entity->getComponent<Components::TileMap>();
		game->drawQueue.push({ (int)transform->position.z, [tilemap, transform](sf::RenderWindow& window, asset::ResourceManager& rManager) {
			auto text = rManager.getAsset<sf::Texture>(tilemap->tilesetId);
			sf::Transform sfTransform;
			sfTransform.translate(std::floor(transform->position.x), std::floor(transform->position.y));
			sfTransform.scale(transform->scale.x, transform->scale.y);
			sfTransform.rotate(transform->rotation);
			if (text != nullptr) {
				sf::RenderStates states;
				states.texture = text.get();
				states.transform = sfTransform;
				for (const auto& kv : tilemap->layers) {
					window.draw(kv.second, states);
				}
			}
		}});
	}
}
