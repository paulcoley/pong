#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

enum class GameState {
	START_MENU,
	PONG
};

namespace pong {
	extern GameState currentGameState;
	extern bool quitGame;
}

void logSDLError(std::ostream &os, const std::string &msg);
std::string getResourcePath();
std::string getResourcePath(const std::string &subDir);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);