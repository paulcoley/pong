#pragma once
#include <list>
#include <SDL.h>

enum COLLISION_LAYER {
	ONE = 1,
	TWO = 2,
	THREE = 4,
	FOUR = 8,
	FIVE = 16,
	SIX = 32,
	SEVEN = 64,
	EIGHT = 128
};

namespace pong {
	extern std::list<std::pair<int, SDL_Rect*>> collisionList;
}