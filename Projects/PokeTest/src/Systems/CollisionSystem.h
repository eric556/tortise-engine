#pragma once
#include <SFML/Graphics.hpp>
#include <queue>

namespace Systems {
	class CollisionSystem {
	public:
		void run(std::priority_queue<DrawEvent, std::vector<DrawEvent>, std::greater<DrawEvent>>& drawQueue);
	};
}