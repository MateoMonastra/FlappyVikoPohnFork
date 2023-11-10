#include "GameLoop.h"

#include "Raylib/header/raylib.h" 

#include "Scenes.h"
#include "Play/Play.h"

namespace FlappyBird
{
	static Scenes scene;

	void GameLoop()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Flappy Bird");
		SetExitKey(NULL);

		//scene = Scenes::Menu;
		scene = Scenes::Play;
		Scenes previousScene = Scenes::Exit;
		bool isNewScene;
		Scenes auxPrevScene = Scenes::Exit;

		do
		{
			isNewScene = (scene != previousScene);
			previousScene = scene;

			switch (scene)
			{
			case Scenes::Menu:
				auxPrevScene = Scenes::Menu;
				break;

			case Scenes::Play:
				RunPlay(isNewScene, previousScene);
				auxPrevScene = Scenes::Play;
				break;

			case Scenes::Pause:
;				auxPrevScene = Scenes::Pause;
				break;

			case Scenes::Rules:
				auxPrevScene = Scenes::Rules;
				break;

			case Scenes::Credits:
				auxPrevScene = Scenes::Credits;
				break;

			case Scenes::LoseScreen:

				break;

			case Scenes::Exit:
				break;

			default:
				break;
			}
		} while (!WindowShouldClose() && scene != Scenes::Exit);

		CloseWindow();
	}
}