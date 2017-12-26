#pragma once
#include <SDL.h>
#include "Vector2.h"

class Ball {
	SDL_Rect m_collision; // Collision. Shape as well if not using a texture.
	Vector2f m_position_default;
	Vector2f m_position;
	Vector2f m_direction;
	float m_speed;
	float m_speed_default;
public:
	Ball(SDL_Rect collision);
	void setSpeed(float);
	SDL_Rect& getCollision();
	Vector2f getWorldCenter();
	void resetPosition();
	void update();
	void render(SDL_Renderer*);
};

