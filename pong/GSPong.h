#pragma once
#include <SDL.h>

namespace pong {
	namespace GSPong {
		void initialize(SDL_Window*, SDL_Renderer*);
		void processInput(SDL_Event&);
		void update();
		void render();
		void enableP1AI(bool);
		void enableP2AI(bool);
		void resetBall();
		void resetPaddles();
		void resetScore();
		void resetGame();
	}
}