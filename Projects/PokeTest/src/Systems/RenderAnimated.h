#pragma once
#include "../PokeGame.h"

namespace Systems {
	class RenderAnimated {
	public:
		void run(float dt, PokeGame* game);
	};
}