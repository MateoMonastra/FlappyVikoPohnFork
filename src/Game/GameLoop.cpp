#include "GameLoop.h"

#include "header/raylib.h"

#include "Scenes.h"

namespace FlappyBird
{
	static Scenes scene;

	void GameLoop()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Asteroids");
		SetExitKey(NULL);
		InitAudioDevice();

		scene = Scenes::Menu;
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

				break;

			case Scenes::Play:

				break;

			case Scenes::Pause:
;
				break;

			case Scenes::Rules:

				break;

			case Scenes::Credits:

				break;

			case Scenes::LoseScreen:

				break;

			case Scenes::Exit:
				break;

			default:
				break;
			}
		} while (!WindowShouldClose() && scene != Scenes::Exit);

		CloseAudioDevice();
		CloseWindow();
	}
}