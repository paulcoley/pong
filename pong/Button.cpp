#include "stdafx.h"
#include "Button.h"
#include <iostream>

Button::Button() : Button({ 0, 0, 200, 100 }) {}

Button::Button(SDL_Rect collision) : Button(collision, { 255, 255, 255, 255 }) {}

Button::Button(SDL_Rect collision, SDL_Color color) {
	m_collision = collision;
	m_color = color;
	m_position = { static_cast<float>(m_collision.x), static_cast<float>(m_collision.y) };
	m_size = { static_cast<float>(m_collision.w), static_cast<float>(m_collision.h) };
	m_text.setPosition(this->getWorldCenter());
}

SDL_Rect& Button::getCollision() {
	return m_collision;
}

Vector2f Button::getWorldCenter() {
	return Vector2f({ m_position.x + (m_size.x / 2), m_position.y + (m_size.y / 2) });
}

void Button::setPosition(Vector2f position) {
	m_position = position;
	m_collision.x = static_cast<int>(m_position.x);
	m_collision.y = static_cast<int>(m_position.y);
}

void Button::setSize(Vector2f size) {
	m_size = size;
	m_collision.w = static_cast<int>(m_size.x);
	m_collision.h = static_cast<int>(m_size.y);
}

void Button::setCallback(std::function<void()> callback) {
	m_callback = callback;
}

void Button::executeCallback() {
	m_callback();
}

Text& Button::text() {
	return m_text;
}

void Button::update() {
}

void Button::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_collision);
	if(m_text.getText().compare("") != 0) m_text.render(renderer);
}
