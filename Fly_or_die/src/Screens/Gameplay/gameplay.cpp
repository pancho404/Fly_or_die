#include "gameplay.h"

#include "raylib.h"

#include <iostream>

#include "Game/game.h"
#include "Screens/Menu/menu.h"
#include "Screens/Controls/controls.h"

bool player2Mode = false;

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
	Texture2D obstacleTexture;
	Rectangle retry;
	Rectangle menu;

	Rectangle menu_button;

	float scrollingBack = 0.0f;
	float scrollingMid = 0.0f;
	float scrollingFore = 0.0f;
	float scrollingCloserFore = 0.0f;
	Texture2D background1;
	Texture2D background2;
	Texture2D background3;
	Texture2D background4;
	Vector2 mause;
	Color mauseColor;

	Vector2 ballPosition;
	float ballSpeedRef;
	float ballAcceleration;
	float ballGravity;
	Color ballColor;
	int ballRadius;
	Texture2D angelFrame1;
	Texture2D angelFrame2;

	Vector2 ballPosition2;
	float ballSpeedRef2;
	float ballAcceleration2;
	Color ballColor2;
	int ballRadius2;


	int impact;
	bool off = true;
	float time;


	void initPlayer() {

		ballPosition = { static_cast<float>(GetScreenWidth()) / 4, static_cast<float>(GetScreenHeight()) / 2 };

		ballColor = MAROON;
		ballRadius = 20;
		ballSpeedRef = 0;
		ballAcceleration = 0;
		ballGravity = 300.0f;
		angelFrame1 = LoadTexture("Res/angel1.png");
		angelFrame2 = LoadTexture("Res/angel2.png");

		ballPosition2 = { static_cast<float>(GetScreenWidth()) / 4, static_cast<float>(GetScreenHeight()) / 2 };
		ballSpeedRef2 = 0;
		ballAcceleration2 = 0;
		ballColor2 = BLUE;
		ballRadius2 = 20;
		if (player2Mode)
		{
			ballPosition = { static_cast<float>(GetScreenWidth()) / 4, static_cast<float>(GetScreenHeight()) / 2 - angelFrame1.height / 2 };
			ballPosition2 = { static_cast<float>(GetScreenWidth()) / 4, static_cast<float>(GetScreenHeight()) / 2 - angelFrame1.height / 2 };
		}
	}

	void initGame() {

		//inicia el audio

		mause = { -100.0f, -100.0f };
		mauseColor = DARKBLUE;

		initPlayer();

		obstacle.x = static_cast<float>(screenWidth);
		obstacle.y = static_cast<float>(screenHeight) - 200;
		//obstaculos
		obstacle.height = 240;
		obstacle.width = 50;
		obstacleTexture = LoadTexture("Res/column.png");

		//Background

		scrollingBack -= 0.1f;
		scrollingMid -= 0.5f;
		scrollingFore -= 1.0f;
		scrollingCloserFore -= 1.5f;
		background1 = LoadTexture("Res/background1.png");
		background2 = LoadTexture("Res/background2.png");
		background3 = LoadTexture("Res/background3.png");
		background4 = LoadTexture("Res/background4.png");


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



		impact = 0;

		mauseradius = 10;

		SetTargetFPS(60);
	}

	void unload() {
		UnloadTexture(angelFrame1);
		UnloadTexture(angelFrame2);
		UnloadTexture(obstacleTexture);
		UnloadTexture(background1);
		UnloadTexture(background2);
		UnloadTexture(background3);
		UnloadTexture(background4);
	}

	void updateInput() {

		if (IsKeyPressed(KEY_P)) inicio = !inicio;

		if (inicio == false) {

			mause = GetMousePosition();
		}

		if (inicio) {

			//jugador 

			if ((IsKeyPressed(KEY_SPACE))) {
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

			if (IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON)) {
				ballAcceleration2 = 0;
				ballSpeedRef2 = -ballGravity / 2;
			}
			else {
				ballAcceleration2 += ballGravity * GetFrameTime();
			}

			if (ballAcceleration2 >= ballGravity) {
				ballAcceleration2 = ballGravity;
			}

			if (ballSpeedRef2 < 0) {
				ballSpeedRef2 += ballAcceleration2 * 2 * GetFrameTime();
			}
			else {
				ballSpeedRef2 += ballAcceleration2 * GetFrameTime();
			}

			if ((ballSpeedRef2 > 0 && ballPosition2.y <= GetScreenHeight() - ballRadius2) || (ballSpeedRef2 < 0 && ballPosition2.y >= ballRadius2))
				ballPosition2.y += ballSpeedRef2 * GetFrameTime();

		}


	}

	void updateGame() {

		if (inicio) {


			scrollingMid -= 50.0f * GetFrameTime();
			scrollingFore -= 100.0f * GetFrameTime();
			scrollingCloserFore -= 150.0f * GetFrameTime();

			if (scrollingBack <= -background4.width) scrollingBack = 0;
			if (scrollingMid <= -background3.width) scrollingMid = 0;
			if (scrollingFore <= -background2.width) scrollingFore = 0;
			if (scrollingCloserFore <= -background1.width) scrollingCloserFore = 0;

			mause = GetMousePosition();

			collision = CheckCollisionCircleRec(ballPosition, static_cast<float>(ballRadius), obstacle);

			if (collision) {
				game::Screens = game::Menu;
				ballPosition.y =static_cast<float>(GetScreenHeight() / 2);
				obstacle.x = screenWidth;
			}

			obstacle.x -= 300.0f * GetFrameTime();
			if (obstacle.x < -100) {
				obstacle.x = screenWidth;
				obstacle.y = static_cast<float>(rand() % 200 + (screenHeight / 2));
			}

		}
		else
		{
			if (CheckCollisionPointRec(mause, menu_button) && IsMouseButtonPressed(MouseButton::MOUSE_LEFT_BUTTON))
			{
				game::Screens = game::Menu;
				ballPosition.y = static_cast<float>(GetScreenHeight() / 2);
				obstacle.x = screenWidth;
			}
		}
	}


	void draw() {

		BeginDrawing();

		ClearBackground(RAYWHITE);

		background1.width = GetScreenWidth();
		background2.width = GetScreenWidth();
		background3.width = GetScreenWidth();
		background4.width = GetScreenWidth();
		background1.height = screenHeight;
		background2.height = screenHeight;
		background3.height = screenHeight;
		background4.height = screenHeight;

		DrawTextureEx(background4, { scrollingBack, 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(background4, { background4.width + scrollingBack, 0 }, 0.0f, 1.0f, WHITE);

		// Draw midground image twice
		DrawTextureEx(background3, { scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(background3, { background3.width + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);

		// Draw foreground image twice
		DrawTextureEx(background2, { scrollingFore, 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(background2, { background2.width + scrollingFore, 0 }, 0.0f, 1.0f, WHITE);

		DrawTextureEx(background1, { scrollingCloserFore, 0 }, 0.0f, 1.0f, WHITE);
		DrawTextureEx(background1, { background1.width + scrollingCloserFore, 0 }, 0.0f, 1.0f, WHITE);



		if (inicio == false) {

			DrawCircleV(mause, static_cast<float>(mauseradius), mauseColor);
			DrawRectangle(static_cast<int>(menu_button.x), static_cast<int>(menu_button.y), static_cast<int>(menu_button.width), static_cast<int>(menu_button.height), BLACK);
			DrawText("Menu", static_cast<int>(menu_button.x) + 18, static_cast<int>(menu_button.y) + 10, 20, WHITE);

		}

		DrawTexture(obstacleTexture, static_cast<int>(obstacle.x - 60.0f), static_cast<int>(obstacle.y - 50.0f), WHITE);


		if (ballSpeedRef < 0)
		{
			DrawTexture(angelFrame2, static_cast<int>(ballPosition.x - ballRadius), static_cast<int>(ballPosition.y - ballRadius * 3), WHITE);
		}
		else
		{
			DrawTexture(angelFrame1, static_cast<int>(ballPosition.x - ballRadius), static_cast<int>(ballPosition.y - ballRadius * 3), WHITE);
		}

		if (player2Mode)
		{
			
			if (ballSpeedRef < 0)
			{
				DrawTexture(angelFrame2, static_cast<int>(ballPosition2.x - ballRadius), static_cast<int>(ballPosition2.y - ballRadius * 3), RED);
			}
			else
			{
				DrawTexture(angelFrame1, static_cast<int>(ballPosition2.x - ballRadius), static_cast<int>(ballPosition2.y - ballRadius * 3), RED);
			}
		}
		



		//Dibujo de pantalla de victoria



		EndDrawing();
	}

	void updateFrame() {

		updateInput();
		updateGame();
		draw();

	}
}



