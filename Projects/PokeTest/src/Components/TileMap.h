#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <ecs/Component.hpp>
#include <map>

namespace Components {
	struct Tile {
		int x;
		int y;
		int width;
		int height;
	};

	class TileMap : public tortoise::ecs::Component {
	public:
		TileMap();
		void debug();
		void setMap(int width, int height, std::map<int, std::vector<std::vector<Tile>>> tiles);
		std::string dump(std::string name);
	public:
		std::string tilesetId;
		std::map<int, sf::VertexArray> layers;
	private:
		char buffer[256];
	};
}