#include "credits.h"

#include "raylib.h"

#include "Game/game.h"

namespace credits {

	void updateCredits();
	void drawCredits();

	static Vector2 mousePoint;
	static Rectangle rec1;
	Texture2D background;

	void initCredits() {

		background = LoadTexture("../res/assets/images/Background.png");

		rec1.x = 25;
		rec1.y = 25;
		rec1.height = 50;
		rec1.width = 100;
	}
	void updateCredits() {

		mousePoint = GetMousePosition();

		if (CheckCollisionPointRec(mousePoint, rec1)) {

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				game::Screens = game::Menu;

			}
		}
	}

	void drawCredits() {

		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawTexture(background, 0, 0, WHITE);

		DrawRectangle(static_cast<int>(rec1.x), static_cast<int>(rec1.y), static_cast<int>(rec1.width), static_cast<int>(rec1.height), BLACK);

		DrawText("atras", static_cast<int>(rec1.x) + 18, static_cast<int>(rec1.y) + 10, 20, WHITE);

		DrawText("Fly or die, por Martin Concetti y Francisco Sanchez", 20, 260, 20, BLACK);
		DrawText("Assets por Martina Angelico Eingelhardt", 20, 280, 20, BLACK);
		DrawText("Grassy Mountains Parallax Bacgkround by vnitti", 20, 300, 20, BLACK);
		DrawText("(https://vnitti.itch.io/grassy-mountains-parallax-background)", 20, 320, 20, BLACK);
		DrawText("Creado usando raylib y sfxr", 130, 340, 20, BLACK);
		DrawText("Version 1.0", 130, 360, 20, BLACK);

		EndDrawing();
	}

	void updateFrameCredits() {
		updateCredits();
		drawCredits();
	}
}