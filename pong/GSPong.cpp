#include "stdafx.h"
#include "GSPong.h"
#include "Paddle.h"
#include "Ball.h"
#include "Collision.h"
#include "Utility.h"
#include "Text.h"

namespace pong {
	namespace GSPong {
		namespace {
			SDL_Window* window;
			SDL_Renderer* renderer;
			Paddle paddle1 = Paddle({});
			Paddle paddle2 = Paddle({});
			Ball ball = Ball({});
			SDL_Rect topBorder;
			SDL_Rect bottomBorder;
			SDL_Rect divider;
			int p1Score;
			int p2Score;
			bool p1AIEnabled;
			bool p2AIEnabled;
			bool paused;
			const int WIN_SCORE = 3;

			void calculateAIMovement(Paddle& paddle, Ball& ball) {
				if(paddle.getCollision().y + (paddle.getCollision().h * 3) / 4 < ball.getCollision().y) {
					paddle.setDirection(PADDLE_DIRECTION::DOWN);
				}
				else if(paddle.getCollision().y > ball.getCollision().y + (ball.getCollision().h * 3) / 4) {
					paddle.setDirection(PADDLE_DIRECTION::UP);
				}
				else {
					paddle.setDirection(PADDLE_DIRECTION::NONE);
				}
			}
		}

		void initialize(SDL_Window* win, SDL_Renderer* rend) {
			window = win;
			renderer = rend;
			p1Score = 0;
			p2Score = 0;
			p1AIEnabled = false;
			p2AIEnabled = false;
			paused = false;

			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			paddle1 = Paddle({ w / 20, 310, 20, 100 });
			paddle2 = Paddle({ w - (w / 20) - 20, 310, 20, 100 });;
			ball = Ball({ w / 2 - 10, h / 2 - 10, 20, 20 });

			paddle1.setSpeed(static_cast<float>(h) / 50.f);
			paddle2.setSpeed(static_cast<float>(h) / 50.f);
			ball.setSpeed(5.f);

			topBorder = { 0, 0, w, h / 25 };
			bottomBorder = { 0, h - (h / 25), w, h / 25 };
			divider = { w / 2 - 10, 0, 20, 20 };

			collisionList.push_back(std::make_pair<int, SDL_Rect*>(COLLISION_LAYER::ONE, &paddle1.getCollision()));
			collisionList.push_back(std::make_pair<int, SDL_Rect*>(COLLISION_LAYER::ONE, &paddle2.getCollision()));
			collisionList.push_back(std::make_pair<int, SDL_Rect*>(COLLISION_LAYER::TWO, &ball.getCollision()));
			collisionList.push_back(std::make_pair<int, SDL_Rect*>(COLLISION_LAYER::THREE, &topBorder));
			collisionList.push_back(std::make_pair<int, SDL_Rect*>(COLLISION_LAYER::THREE, &bottomBorder));
		}
		void processInput(SDL_Event& e) {
			if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						paddle1.setDirection(PADDLE_DIRECTION::UP);
						break;
					case SDLK_s:
						paddle1.setDirection(PADDLE_DIRECTION::DOWN);
						break;
					case SDLK_UP:
						paddle2.setDirection(PADDLE_DIRECTION::UP);
						break;
					case SDLK_DOWN:
						paddle2.setDirection(PADDLE_DIRECTION::DOWN);
						break;
				}
			}

			if(e.type == SDL_KEYUP) {
				switch(e.key.keysym.sym) {
					case SDLK_w:
						paddle1.setDirection(PADDLE_DIRECTION::NONE);
						break;
					case SDLK_s:
						paddle1.setDirection(PADDLE_DIRECTION::NONE);
						break;
					case SDLK_UP:
						paddle2.setDirection(PADDLE_DIRECTION::NONE);
						break;
					case SDLK_DOWN:
						paddle2.setDirection(PADDLE_DIRECTION::NONE);
						break;
					case SDLK_ESCAPE:
						pong::currentGameState = GameState::START_MENU;
						break;
					case SDLK_p:
						paused = paused ? false : true;
						break;
				}
			}
		}
		void update() {
			if(paused) return;
			if(p1Score >= WIN_SCORE || p2Score >= WIN_SCORE) return;

			int w, h;
			SDL_GetWindowSize(window, &w, &h);

			if(p1AIEnabled) calculateAIMovement(paddle1, ball);
			if(p2AIEnabled) calculateAIMovement(paddle2, ball);

			paddle1.update();
			paddle2.update();
			ball.update();

			if(ball.getCollision().x < 0) {
				p2Score++;
				ball.resetPosition();
			}
			else if(ball.getCollision().x > w) {
				p1Score++;
				ball.resetPosition();
			}
		}
		void render() {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderClear(renderer);

			int w, h;
			SDL_GetWindowSize(window, &w, &h);

			SDL_Color fontColor = { 255, 255, 255, 255 };
			Text playerOneScore = Text(std::to_string(p1Score));
			Text playerTwoScore = Text(std::to_string(p2Score));
			playerOneScore.setPosition({ static_cast<float>(w / 3), static_cast<float>(h / 10) });
			playerTwoScore.setPosition({ static_cast<float>(w - (w / 3)), static_cast<float>(h / 10) });
			playerOneScore.setFontSize(128);
			playerTwoScore.setFontSize(128);
			playerOneScore.setColor({ 255, 255, 255, 255 });
			playerTwoScore.setColor({ 255, 255, 255, 255 });

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &topBorder);
			SDL_RenderFillRect(renderer, &bottomBorder);

			do {
				SDL_RenderFillRect(renderer, &divider);
				divider.y += h / 20;
			} while(divider.y <= h);
			divider.y = h / 25;

			paddle1.render(renderer);
			paddle2.render(renderer);
			ball.render(renderer);
			playerOneScore.render(renderer);
			playerTwoScore.render(renderer);

			if(p1Score >= WIN_SCORE || p2Score >= WIN_SCORE) {
				Text winner = p1Score >= WIN_SCORE ? Text("Player 1 Wins!") : Text("Player 2 Wins!");
				winner.setPosition({ static_cast<float>(w / 2 + 20), static_cast<float>(h / 2) });
				winner.setFontSize(128);
				winner.setColor({ 255, 255, 255, 255 });
				winner.render(renderer);
			}

			SDL_RenderPresent(renderer);
		}
		void enableP1AI(bool isEnabled) {
			p1AIEnabled = isEnabled;
		}
		void enableP2AI(bool isEnabled) {
			p2AIEnabled = isEnabled;
		}
		void resetBall() {
			ball.resetPosition();
		}
		void resetPaddles() {
			int w, h;
			SDL_GetWindowSize(window, &w, &h);
			paddle1 = Paddle({ w / 20, 310, 20, 100 });
			paddle2 = Paddle({ w - (w / 20) - 20, 310, 20, 100 });;
			paddle1.setSpeed(static_cast<float>(h) / 50.f);
			paddle2.setSpeed(static_cast<float>(h) / 50.f);
		}
		void resetScore() {
			p1Score = 0;
			p2Score = 0;
		}
		void resetGame() {
			paused = false;
			pong::GSPong::resetScore();
			pong::GSPong::resetPaddles();
			pong::GSPong::resetBall();
		}
	}
}