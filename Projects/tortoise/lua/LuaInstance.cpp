#include "LuaInstance.h"
#include "../resources/ResourceManager.h"
#include <SFML/Graphics.hpp>

void tortoise::lua::LuaInstance::Init(std::string assetsPath) {
	MainState = sol::state();
	MainState.open_libraries(sol::lib::base, sol::lib::package, sol::lib::os, sol::lib::math);
	const std::string package_path = MainState["package"]["path"];
	// MainState["package"]["path"] = package_path + ((!package_path.empty()) ? ";" : "") + "Assets/Scripts/?.lua;Assets/Scripts/?/?.lua";
	MainState["package"]["path"] = package_path + ((!package_path.empty()) ? ";" : "") + assetsPath;

	MainState.new_usertype<sf::Vector2f>("Vector2",
		sol::constructors <sf::Vector2f(float, float)>(),
		"x", &sf::Vector2f::x,
		"y", &sf::Vector2f::y
	);

	MainState.new_usertype<sf::Vector3f>("Vector3",
		sol::constructors <sf::Vector3f(float, float, float)>(),
		"x", &sf::Vector3f::x,
		"y", &sf::Vector3f::y,
		"z", &sf::Vector3f::z,
		sol::meta_function::addition, sol::resolve<sf::Vector3f(const sf::Vector3f&, const sf::Vector3f&)>(sf::operator+),
		sol::meta_function::subtraction, sol::resolve<sf::Vector3f(const sf::Vector3f&, const sf::Vector3f&)>(sf::operator-),
		sol::meta_function::multiplication, sol::resolve<sf::Vector3f(const sf::Vector3f&, float)>(sf::operator*)
	);

	MainState.new_usertype<sf::IntRect>("IntRect",
		sol::constructors<sf::IntRect(int, int, int, int)>(),
		"top", &sf::IntRect::top,
		"left", &sf::IntRect::left,
		"width", &sf::IntRect::width,
		"height", &sf::IntRect::height
	);

	MainState.new_usertype<sf::FloatRect>("FloatRect",
		sol::constructors<sf::FloatRect(float, float, float, float)>(),
		"top", &sf::FloatRect::top,
		"left", &sf::FloatRect::left,
		"width", &sf::FloatRect::width,
		"height", &sf::FloatRect::height
	);

	MainState.new_usertype<sf::Color>("Color",
		sol::constructors < sf::Color(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha)>(),
		"r", &sf::Color::r,
		"g", &sf::Color::g,
		"b", &sf::Color::b,
		"a", &sf::Color::a
	);

	MainState.new_usertype<sf::RectangleShape>("RectangleShape",
		sol::constructors<sf::RectangleShape(const sf::Vector2f& size)>(),
		"setSize", &sf::RectangleShape::setSize,
		"setColor", &sf::RectangleShape::setFillColor,
		"setOrigin", sol::resolve<void(float, float)>(&sf::RectangleShape::setOrigin)
	);

	MainState.new_usertype<sf::Sprite>("Sprite",
		"setOrigin", sol::resolve<void(float, float)>(&sf::Sprite::setOrigin)
	);

	MainState.new_usertype<ecs::EntityManager>("EntityManager",
		"entities", sol::var(std::ref(ecs::EntityManager::entities)),
		"entityCount", sol::var(std::ref(ecs::EntityManager::entityCount)),
		"createEntity", sol::resolve<std::shared_ptr<ecs::Entity>()>(&ecs::EntityManager::createEntity),
		"createEntityOnParent", sol::resolve<std::shared_ptr<ecs::Entity>(std::shared_ptr<ecs::Entity>&)>(&ecs::EntityManager::createEntity),
		"deleteEntity", &ecs::EntityManager::deleteEntity,
		"getEntity", &ecs::EntityManager::getEntityByID
	);

	MainState["entityManager"] = ecs::EntityManager();

	MainState.new_usertype<ecs::Entity>("Entity",
		sol::constructors<ecs::Entity(unsigned int)>(),
		"id", &ecs::Entity::id,
		"name", &ecs::Entity::name,
		"addTag", &ecs::Entity::addComponent,
		"removeTag", &ecs::Entity::removeComp,
		"addChild", &ecs::Entity::addChild,
		"removeChild", &ecs::Entity::removeChild,
		"dump", [](ecs::Entity& self) {
			for (auto& comp : self.components) {
				std::cout << comp->dump(self.name) << std::endl;
			}
		}
	);

	MainState.new_usertype<asset::ResourceManager>("ResourceManager", 
		"loadTexture", &asset::ResourceManager::LoadTexture,
		"getTextureAsset", &asset::ResourceManager::getAsset<sf::Texture>
	);

	MainState["resourceManager"] = asset::ResourceManager();

	MainState.create_named_table("Systems");

	MainState.set_function("getKeyDown", [](unsigned int key) -> bool {
		return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
	});
}

sol::state_view tortoise::lua::LuaInstance::getStateView() {
	return sol::state_view(MainState);
}

void tortoise::lua::LuaInstance::resetState() {
	MainState = sol::state();
}
