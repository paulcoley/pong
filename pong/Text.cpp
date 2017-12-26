#include "stdafx.h"
#include "Text.h"
#include "Utility.h"
#include <SDL_ttf.h>

Text::Text() : Text("") {}

Text::Text(std::string text) {
	m_text = text;
	m_color = {0, 0, 0, 255};
	m_fontSize = 12;
	m_position = {0.f, 0.f};
	m_font = getResourcePath() + "PongPixel.ttf";
}

void Text::setText(std::string text) {
	m_text = text;
}

std::string Text::getText() {
	return m_text;
}

void Text::setPosition(Vector2f position) {
	m_position = position;
}

void Text::setFontSize(int fontSize) {
	m_fontSize = fontSize;
}

void Text::setColor(SDL_Color color) {
	m_color = color;
}

Vector2f Text::getPosition() {
	return m_position;
}

void Text::render(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont(m_font.c_str(), m_fontSize);
	if(font == nullptr) {
		logSDLError(std::cout, "TTF_OpenFont");
		return;
	}
	SDL_Surface* surf = TTF_RenderText_Blended(font, m_text.c_str(), m_color);
	if(surf == nullptr) {
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	if(texture == nullptr) {
		logSDLError(std::cout, "CreateTexture");
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);


	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	renderTexture(texture, renderer, static_cast<int>(m_position.x) - (w / 2), static_cast<int>(m_position.y) - (h / 2));
	SDL_DestroyTexture(texture);
}
