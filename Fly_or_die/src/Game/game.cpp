#include "Game\game.h"

#include "raylib.h"

#include "Screens\Menu\menu.h"
#include "Screens\Controls\controls.h"
#include "Screens\Credits\credits.h"
#include "Screens\Gameplay\gameplay.h"

namespace game {
	static void change();

	const int screenWidth = 800;
	const int screenHeight = 450;

	GameScreen Screens;


	int core()
	{
		InitWindow(screenWidth, screenHeight, "Fly or die");

		gameplay::initGame();
		menu::initMenu();
		controls::initControls();
		credits::initCredits();
		while (!WindowShouldClose())
		{
			change();

		}
		gameplay::unload();
		CloseWindow();

		return 0;
	}

	static void change() {

		switch (Screens) {
		case Menu:
			menu::updateMenu();
			break;
		case Game:
			gameplay::updateFrame();
			break;
		case Controls:
			controls::updateFrameControls();
			break;
		case Credits:
			credits::updateFrameCredits();
			break;
		}
	}

}