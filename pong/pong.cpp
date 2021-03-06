// pong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include <ctime>
#include <SDL_ttf.h>
#include <unordered_map>
#include <functional>
#include "Vector2.h"
#include "GSPong.h"
#include "GSMainMenu.h"
#include "Utility.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float TICK_RATE = 1000.f / 60.f;

std::unordered_map < GameState, std::function<void(SDL_Event&)>> processInputList;
std::unordered_map < GameState, std::function<void()>> updateList;
std::unordered_map < GameState, std::function<void()>> renderList;

int main(int argc, char **argv) {
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		SDL_DestroyWindow(window);
		return 1;
	}
	if(TTF_Init() != 0) {
		logSDLError(std::cout, "TTF_Init");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	processInputList[GameState::START_MENU] = &pong::GSMainMenu::processInput;
	processInputList[GameState::PONG] = &pong::GSPong::processInput;
	updateList[GameState::START_MENU] = &pong::GSMainMenu::update;
	updateList[GameState::PONG] = &pong::GSPong::update;
	renderList[GameState::START_MENU] = &pong::GSMainMenu::render;
	renderList[GameState::PONG] = &pong::GSPong::render;

	pong::currentGameState = GameState::START_MENU;

	pong::GSMainMenu::initialize(window, renderer);
	pong::GSPong::initialize(window, renderer);

	float startTime = static_cast<float>(SDL_GetTicks());
	float extraTime = 0.f;

	while(!pong::quitGame) {
		SDL_Event e;

		while(SDL_PollEvent(&e)) {
			processInputList[pong::currentGameState](e);

			if(e.type == SDL_QUIT) {
				pong::quitGame = true;
			}
		}

		float timeSinceUpdate = static_cast<float>(SDL_GetTicks()) - startTime + extraTime;
		if(timeSinceUpdate >= TICK_RATE) {
			while(timeSinceUpdate >= TICK_RATE) {
				updateList[pong::currentGameState]();

				timeSinceUpdate -= TICK_RATE;
			}
			startTime = static_cast<float>(SDL_GetTicks());
			extraTime = timeSinceUpdate;
		}

		renderList[pong::currentGameState]();
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}