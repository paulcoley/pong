#include "stdafx.h"
#include "Ball.h"
#include "Collision.h"
#include <iostream>
#include <ctime>


Ball::Ball(SDL_Rect collision) {
	std::srand(std::time(nullptr));

	m_collision = collision;
	m_direction = { std::rand() % 2 ? 1.f : -1.f, std::rand() % 2 ? 1.f : -1.f };
	m_position = { static_cast<float>(m_collision.x), static_cast<float>(m_collision.y) };
	m_position_default = m_position;
	m_speed = 0.f;
	m_speed_default = 0.f;

	m_direction.convertToUnitVector();
}

void Ball::setSpeed(float speed) {
	m_speed = speed;
	m_speed_default = speed;
}

SDL_Rect& Ball::getCollision() {
	return m_collision;
}

Vector2f Ball::getWorldCenter() {
	return Vector2f({ m_position.x + static_cast<float>(m_collision.w), m_position.y + static_cast<float>(m_collision.h) });
}

void Ball::resetPosition() {
	m_position = m_position_default;
	m_speed = m_speed_default;
	m_collision = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_collision.w, m_collision.h };
}

void Ball::update() {
	m_position.x += m_direction.x * m_speed;
	m_collision.x = static_cast<int>(m_position.x);
	m_position.y += m_direction.y * m_speed;
	m_collision.y = static_cast<int>(m_position.y);
	for(auto& collider : pong::collisionList) {
		if((collider.first & COLLISION_LAYER::ONE) && &m_collision != collider.second) {
			SDL_Rect intersection;
			if(SDL_IntersectRect(&m_collision, collider.second, &intersection) == SDL_TRUE) {
				m_direction.x *= -1.f;
				m_position.x += static_cast<float>(m_speed) * m_direction.x;
				m_collision.x = static_cast<int>(m_position.x);
				m_speed += 1.f;
			}
		}
		else if((collider.first & COLLISION_LAYER::THREE) && &m_collision != collider.second) {
			SDL_Rect intersection;
			if(SDL_IntersectRect(&m_collision, collider.second, &intersection) == SDL_TRUE) {
				m_direction.y *= -1.f;
				m_position.y += static_cast<float>(m_speed) * m_direction.y;
				m_collision.y = static_cast<int>(m_position.y);
			}
		}
	}
}

void Ball::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_collision);
}
