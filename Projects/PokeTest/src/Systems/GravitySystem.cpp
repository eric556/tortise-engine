#include "GravitySystem.h"
#include <ecs/EntityManager.hpp>

using namespace tortoise;

namespace Systems {
	void GravitySystem::run() {
		ecs::EntityManager eManager;
		auto physicsEntities = eManager.getEntitiesByComponent<Components::KineticBody>(Components::GRAVITY);

		for (auto entity : physicsEntities) {
			auto kb = entity->getComponent<Components::KineticBody>();
			kb->forceAccumulator += sf::Vector3f(0.0f, GRAV_CONST * kb->mass, 0.0f);
		}
	}
}