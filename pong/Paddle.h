#pragma once
#include <SDL.h>
#include "Vector2.h"

enum class PADDLE_DIRECTION {
	UP,
	DOWN,
	NONE
};

class Paddle {
private:
	SDL_Rect m_collision; // Collision. Shape as well if not using a texture.
	Vector2f m_position;
	float m_direction; // -1.f for up, 1.f for down, 0.f for no movement
	float m_speed;
public:
	Paddle(SDL_Rect);
	void setDirection(PADDLE_DIRECTION);
	void setSpeed(float);
	SDL_Rect& getCollision();
	void update();
	void render(SDL_Renderer*);
};