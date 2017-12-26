#include "stdafx.h"
#include "Paddle.h"
#include "Collision.h"
#include <iostream>

Paddle::Paddle(SDL_Rect collision) {
	m_collision = collision;
	m_direction = 0.f;
	m_position = { static_cast<float>(m_collision.x), static_cast<float>(m_collision.y) };
	m_speed = 0.f;
}

void Paddle::setDirection(PADDLE_DIRECTION direction) {
	if(direction == PADDLE_DIRECTION::UP) m_direction = -1.f;
	else if(direction == PADDLE_DIRECTION::DOWN) m_direction = 1.f;
	else if(direction == PADDLE_DIRECTION::NONE) m_direction = 0.f;
}

void Paddle::setSpeed(float speed) {
	m_speed = speed;
}

SDL_Rect& Paddle::getCollision() {
	return m_collision;
}

void Paddle::update() {
	m_position.y += m_direction * m_speed;
	m_collision.y = static_cast<int>(m_position.y);
	for(auto& collider : pong::collisionList) {
		if((collider.first & COLLISION_LAYER::THREE) && &m_collision != collider.second) {
			SDL_Rect intersection;
			if(SDL_IntersectRect(&m_collision, collider.second, &intersection) == SDL_TRUE) {
				m_position.y += -m_direction * intersection.h;
				m_collision.y = static_cast<int>(m_position.y);
			}
		}
	}
}

void Paddle::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_collision);
}
