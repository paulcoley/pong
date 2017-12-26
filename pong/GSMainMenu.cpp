#include "stdafx.h"
#include "GSMainMenu.h"
#include "Button.h"
#include "Utility.h"
#include "GSPong.h"

namespace pong {
	namespace GSMainMenu {
		namespace {
			SDL_Window* window;
			SDL_Renderer* renderer;
			Button newGame = Button({}, {});
			Button aiGame = Button({}, {});
			Button botGame = Button({}, {});
			Button quitGame = Button({}, {});
		}

		void initialize(SDL_Window* win, SDL_Renderer* rend) {
			window = win;
			renderer = rend;

			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			newGame = Button({(w / 2) - 100, (h / 5) - 50, 200, 100}, {255, 255, 255, 255});
			newGame.text().setText("Two Player");
			newGame.text().setFontSize(32);
			newGame.setCallback([]() {
				pong::GSPong::resetGame();
				pong::GSPong::enableP1AI(false);
				pong::GSPong::enableP2AI(false);
				pong::currentGameState = GameState::PONG;
			});

			aiGame = Button({ (w / 2) - 100, 2*(h / 5) - 50, 200, 100 }, { 255, 255, 255, 255 });
			aiGame.text().setText("Vs AI");
			aiGame.text().setFontSize(32);
			aiGame.setCallback([]() {
				pong::GSPong::resetGame();
				pong::GSPong::enableP1AI(false);
				pong::GSPong::enableP2AI(true);
				pong::currentGameState = GameState::PONG;
			});

			botGame = Button({ (w / 2) - 100, 3*(h / 5) - 50, 200, 100 }, { 255, 255, 255, 255 });
			botGame.text().setText("Bot Game");
			botGame.text().setFontSize(32);
			botGame.setCallback([]() {
				pong::GSPong::resetGame();
				pong::GSPong::enableP1AI(true);
				pong::GSPong::enableP2AI(true);
				pong::currentGameState = GameState::PONG;
			});

			quitGame = Button({ (w / 2) - 100, 4*(h / 5) - 50, 200, 100 }, { 255, 255, 255, 255 });
			quitGame.text().setText("Quit Game");
			quitGame.text().setFontSize(32);
			quitGame.setCallback([]() { pong::quitGame = true; });
		}
		void processInput(SDL_Event& e) {
			if(e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					if(SDL_IntersectRectAndLine(&newGame.getCollision(), &x, &y, &x, &y) == SDL_TRUE) {
						newGame.executeCallback();
					}
					else if(SDL_IntersectRectAndLine(&aiGame.getCollision(), &x, &y, &x, &y) == SDL_TRUE) {
						aiGame.executeCallback();
					}
					else if(SDL_IntersectRectAndLine(&botGame.getCollision(), &x, &y, &x, &y) == SDL_TRUE) {
						botGame.executeCallback();
					}
					else if(SDL_IntersectRectAndLine(&quitGame.getCollision(), &x, &y, &x, &y) == SDL_TRUE) {
						quitGame.executeCallback();
					}
				}
			}
		}
		void update() {

		}
		void render() {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);
			newGame.render(renderer);
			aiGame.render(renderer);
			botGame.render(renderer);
			quitGame.render(renderer);

			SDL_RenderPresent(renderer);
		}
	}
}