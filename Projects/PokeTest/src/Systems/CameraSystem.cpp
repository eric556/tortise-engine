#include "CameraSystem.h"
#include <ecs/EntityManager.hpp>
#include "../Components/Camera.h"
#include "../Components/Transform.h"

using namespace tortoise;
using namespace ecs;

void Systems::CameraSystem::run(sf::RenderWindow& window)
{
	ecs::EntityManager eManager;
	auto entities = eManager.getEntitiesByComponents < Components::Camera>();
	for (auto entity : entities) {
		auto camera = entity->getComponent<Components::Camera>();
		if (auto spt = camera->followEntity.lock()) {
			auto transform = spt->getComponent<Components::Transform>();
			camera->view.setCenter(std::floor(transform->position.x), std::floor(transform->position.y));
			window.setView(camera->view);
		}
	}
}
