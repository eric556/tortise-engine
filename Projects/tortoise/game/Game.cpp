#include "Game.h"

tortoise::game::Game::Game(std::string name, unsigned int width, unsigned int height, std::string assetPath) : window(sf::VideoMode(width, height), name) {
	lua.Init(assetPath);
	// Components::ComponenetRegister::RegisterComponents(lua);
	running = true;
}

void tortoise::game::Game::Start(std::string filepath)
{
	this->registerLua();
	Load(filepath);
	this->Start();
}

void tortoise::game::Game::Start()
{
	sol::state_view view = lua.getStateView();
	window.resetGLStates();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
			}
		}


		sf::Time dt = deltaClock.restart();
		view.script("update(" + std::to_string(dt.asSeconds()) + ")");
		window.clear(sf::Color::Black);
		view.script("draw(" + std::to_string(dt.asSeconds()) + ")");
		window.display();
	}
}

sol::function_result tortoise::game::Game::Load(std::string filepath)
{
	sol::state_view view = lua.getStateView();
	auto result = view.safe_script_file(filepath, sol::script_throw_on_error, sol::load_mode::text);

	view.script("load()");

	return result;
}
