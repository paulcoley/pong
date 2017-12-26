#pragma once
#include <string>
#include <SDL.h>
#include "Vector2.h"
#include "Text.h"
#include <functional>

class Button {
private:
	SDL_Rect m_collision;
	Vector2f m_position;
	Vector2f m_size;
	SDL_Color m_color;
	Text m_text;
	std::function<void()> m_callback;
public:
	Button();
	Button(SDL_Rect);
	Button(SDL_Rect, SDL_Color);
	SDL_Rect& getCollision();
	Vector2f getWorldCenter();
	void setPosition(Vector2f);
	void setSize(Vector2f);
	void setCallback(std::function<void()>);
	void executeCallback();
	Text& text();
	void update();
	void render(SDL_Renderer*);
};