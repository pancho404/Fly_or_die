#include "raylib.h"

#include "Controls.h"

#include <iostream>

#include "Game/Game.h"

namespace controls {

	void updateControls();
	void drawControls();

	Texture2D background;

	int foo[] = { 16, 2, 77, 40, 12071 };
	int* ptr = foo;

	static Rectangle rect1;
	static Rectangle rect2;
	static Rectangle rect3;

	static Rectangle player1;
	static Rectangle player2;

	Vector2 mause;
	Color mauseColor;

	Color player1Color = DARKBLUE;
	Color player2Color = GOLD;

	bool colorChange = false;
	bool colorChange2 = false;

	bool controlChange = false;
	bool controlChange2 = false;

	int count1;
	int count2;
	int count3;
	int count4;

	int mauseradius;

	char upPlayer1 = 'Q';
	char downPlayer1 = 'A';
	char upPlayer2 = 'P';
	char downPlayer2 = 'L';

	void initControls() {
		
		player1.x = static_cast<float>(GetScreenWidth()) / 6 - 120;
		player1.y = static_cast<float>(GetScreenHeight()) / 4 + 50;
		player1.height = 80;
		player1.width = 10;

		player2.x = static_cast<float>(GetScreenWidth()) - 30;
		player2.y = static_cast<float>(GetScreenHeight()) / 4 + 50;
		player2.height = 80;
		player2.width = 10;

		rect1.x = 25;
		rect1.y = 25;
		rect1.height = 50;
		rect1.width = 100;

		rect2.x = 0;
		rect2.y = static_cast<float>(GetScreenHeight()) - 50;
		rect2.height = 50;
		rect2.width = 100;

		rect3.x = static_cast<float>(GetScreenWidth()) - 100;
		rect3.y = static_cast<float>(GetScreenHeight()) - 50;
		rect3.height = 50;
		rect3.width = 100;

		int count1 = 0;
		int count2 = 0;

		mause = { -100.0f, -100.0f };
		mauseColor = DARKBLUE;
		mauseradius = 10;



	}

	void updateControls() {

		mause = GetMousePosition();

		if (CheckCollisionPointRec(mause, rect1)) {

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				game::Screens = game::Menu;
			}

		}

		colorChange = CheckCollisionCircleRec(mause, static_cast<float>(mauseradius), player1);
		colorChange2 = CheckCollisionCircleRec(mause, static_cast<float>(mauseradius), player2);


		if (CheckCollisionPointRec(mause, rect1)) {

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				game::Screens = game::Menu;

			}

		}


	}

	void drawControls() {

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawTexture(background, 0, 0, WHITE);

		DrawRectangle(static_cast<int>(player1.x), static_cast<int>(player1.y), static_cast<int>(player1.width), static_cast<int>(player1.height), player1Color);
		DrawRectangle(static_cast<int>(player2.x), static_cast<int>(player2.y), static_cast<int>(player2.width), static_cast<int>(player2.height), player2Color);

		DrawRectangle(static_cast<int>(rect1.x), static_cast<int>(rect1.y), static_cast<int>(rect1.width), static_cast<int>(rect1.height), BLACK);
		DrawRectangle(static_cast<int>(rect2.x), static_cast<int>(rect2.y), static_cast<int>(rect2.width), static_cast<int>(rect2.height), BLACK);
		DrawRectangle(static_cast<int>(rect3.x), static_cast<int>(rect3.y), static_cast<int>(rect3.width), static_cast<int>(rect3.height), BLACK);

		ClearBackground(RAYWHITE);
		DrawText("atras", static_cast<int>(rect1.x) + 18, static_cast<int>(rect1.y) + 10, 20, WHITE);
		DrawText("Spacebar para saltar (jugador blanco)", 40, 100, 20, BLACK);
		DrawText("Click para saltar (jugador rojo)", 40, 120, 20, BLACK);
		DrawText("P para empezar", 40, 140, 20, BLACK);




		DrawCircleV(mause, static_cast<float>(mauseradius), mauseColor);

		EndDrawing();
	}

	void updateFrameControls() {
		updateControls();
		drawControls();
	}

}