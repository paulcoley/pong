#pragma once
#include <string>
#include <SDL.h>
#include "Vector2.h"

class Text {
private:
	std::string m_text;
	std::string m_font;
	SDL_Color m_color;
	int m_fontSize;
	Vector2f m_position;
public:
	Text();
	Text(std::string);
	void setText(std::string);
	std::string getText();
	void setPosition(Vector2f);
	void setFontSize(int);
	void setColor(SDL_Color);
	Vector2f getPosition();
	void render(SDL_Renderer*);
};

