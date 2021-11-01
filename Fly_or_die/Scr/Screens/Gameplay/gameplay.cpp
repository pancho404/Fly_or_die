#include "gameplay.h"

#include "raylib.h"

#include<iostream>

#include "Game/game.h"
#include "Screens/Controls/controls.h"


namespace gameplay {

	void initPlayer();
	void updateInput();
	void updateGame();
	void draw();

	game::GameScreen Screens;

	const int screenWidth = 800;
	const int screenHeight = 450;

	
	bool inicio = false;

	int mauseradius;

	bool collision = false;

	Rectangle obstacle;

	Rectangle retry;
	Rectangle menu;

	Rectangle menu_button;

	Texture2D background;
	Vector2 mause;
	Color mauseColor;

	Vector2 ballPosition;
	float ballSpeedRef;
	float ballAcceleration;
	float ballGravity;
	Color ballColor;
	int ballRadius;
	

	int impact;
	bool off = true;
	float time;

	
	void initPlayer() {

		obstacle.height = 200;
		obstacle.width = 100;


	}

	void initGame() {

		//inicia el audio

		mause = { -100.0f, -100.0f };
		mauseColor = DARKBLUE;

		initPlayer();

		obstacle.x = static_cast<float>(screenWidth) ;
		obstacle.y = static_cast<float>(screenHeight) -200;

	
		//Botones
		menu.height = 40;
		menu.width = 90;
		menu.x = static_cast<float>(screenWidth) / 2 + 80;
		menu.y = static_cast<float>(screenHeight) / 4 + 50;

		retry.height = 40;
		retry.width = 100;
		retry.x = static_cast<float>(screenWidth) / 2 + 80;
		retry.y = static_cast<float>(screenHeight) / 4 + 100;

		menu_button.x = static_cast<float>(GetScreenWidth()) - 100;
		menu_button.y = 0;
		menu_button.height = 50;
		menu_button.width = 100;

		//pelota
		ballPosition = { static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2 };
		ballColor = MAROON;
		ballRadius = 20;
		ballSpeedRef = 0;
		ballAcceleration = 0;
		ballGravity = 300.0f;

		impact = 0;

		mauseradius = 10;

		SetTargetFPS(60);
	}

	void unload() {
		
	}

	static void updateInput() {

		if (IsKeyPressed(32)) inicio = !inicio;

		if (inicio == false) {

			mause = GetMousePosition();


		}

		if (inicio) {

			//jugador 
			/*if (IsKeyDown(controls::upPlayer1)) {

				if (ballPosition.y > 0) {

					ballPosition.y -= 5.0f;

				}
			}

			if (IsKeyDown(controls::downPlayer1)) {

				if (ballPosition.y  < GetScreenHeight()) {

					ballPosition.y += 5.0f;

				}
			}*/

			if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
				ballAcceleration = 0;
				ballSpeedRef = -ballGravity / 2;
			}
			else {
				ballAcceleration += ballGravity * GetFrameTime();
			}

			if (ballAcceleration >= ballGravity) {
				ballAcceleration = ballGravity;
			}

			if (ballSpeedRef < 0) {
				ballSpeedRef += ballAcceleration * 2 * GetFrameTime();
			}
			else {
				ballSpeedRef += ballAcceleration * GetFrameTime();
			}

			if ((ballSpeedRef > 0 && ballPosition.y <= GetScreenHeight() - ballRadius) || (ballSpeedRef < 0 && ballPosition.y >= ballRadius))
				ballPosition.y += ballSpeedRef * GetFrameTime();

		}


	}

	static void updateGame() {

		if (inicio) {
			mause = GetMousePosition();

			collision = CheckCollisionCircleRec(ballPosition, static_cast<float>(ballRadius), obstacle);

			if (collision) {
				game::Screens = game::Menu;
				ballPosition.y = 10;
			}

			obstacle.x -= 5.0f;
			if (obstacle.x < -100) {
				obstacle.x = screenWidth;
			}

		}
	}


	static void draw() {

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawTexture(background, 0, 0, WHITE);

		

			if (inicio == false) {

				DrawCircleV(mause, static_cast<float>(mauseradius), mauseColor);
				DrawRectangle(static_cast<int>(menu_button.x), static_cast<int>(menu_button.y), static_cast<int>(menu_button.width), static_cast<int>(menu_button.height), BLACK);
				DrawText("Menu", static_cast<int>(menu_button.x) + 18, static_cast<int>(menu_button.y) + 10, 20, WHITE);

			}

			DrawRectangle(static_cast<int>(obstacle.x), static_cast<int>(obstacle.y), static_cast<int>(obstacle.width), static_cast<int>(obstacle.height), controls::player1Color);

			DrawRectangleRec(obstacle, controls::player1Color);


			DrawCircleV(ballPosition, static_cast<float>(ballRadius), ballColor);

		

		//Dibujo de pantalla de victoria

		

		EndDrawing();
	}

	void updateFrame() {

		updateInput();
		updateGame();
		draw();

	}
}



