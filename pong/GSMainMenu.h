#pragma once
#include <SDL.h>

namespace pong {
	namespace GSMainMenu {
		void initialize(SDL_Window*, SDL_Renderer*);
		void processInput(SDL_Event&);
		void update();
		void render();
	}
}