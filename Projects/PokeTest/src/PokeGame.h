#pragma once
#include <game/Game.h>
#include <queue>
#include <functional>

#include "Systems/GravitySystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/RenderSpriteSystem.h"
#include "Systems/PlayerInputSystem.h"
#include "Systems/RenderAnimated.h"
#include "Systems/RenderTilemapSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/CameraSystem.h"


struct DrawEvent {
	int zIndex;
	std::function<void(sf::RenderWindow&, tortoise::asset::ResourceManager&)> drawFunction;
	friend bool operator<(const DrawEvent& lhs, const DrawEvent& rhs) {
		return lhs.zIndex < rhs.zIndex;
	}

	friend bool operator>(const DrawEvent& lhs, const DrawEvent& rhs) {
		return lhs.zIndex > rhs.zIndex;
	}
};

class PokeGame : public tortoise::game::Game{
public:
	PokeGame();
	std::priority_queue<DrawEvent, std::vector<DrawEvent>, std::greater<DrawEvent>> drawQueue;
	// Inherited via Game
	virtual void registerLua() override;

private:
	Systems::GravitySystem gravSys;
	Systems::PlayerInputSystem playerInputSys;
	Systems::PhysicsSystem physSys;
	Systems::RenderSystem renderSys;
	Systems::RenderSpriteSystem renderTextureSys;
	Systems::RenderAnimated renderAnimatedSys;
	Systems::RenderTilemapSystem renderTilemapSys;
	Systems::CollisionSystem colSys;
	Systems::CameraSystem camSys;
};