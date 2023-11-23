#include "GameLoop.h"

#include "Raylib/header/raylib.h" 

#include "Scenes.h"
#include "Menu/Menu.h"
#include "Play/Play.h"
#include "Pause/Pause.h"
#include "Credits/Credits.h"
#include "Rules/Rules.h"

namespace FlappyBird
{
	static Scenes scene;

	void GameLoop()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Flappy Viko");
		SetExitKey(NULL);

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
				RunMenu(scene, isNewScene);
				auxPrevScene = Scenes::Menu;
				break;

			case Scenes::Play:
				RunPlay(isNewScene, auxPrevScene, scene);
				auxPrevScene = Scenes::Play;
				break;

			case Scenes::Pause:
				RunPause(scene, isNewScene);
				auxPrevScene = Scenes::Pause;
				break;

			case Scenes::Rules:
				RunRules(scene, isNewScene);
				auxPrevScene = Scenes::Rules;
				break;

			case Scenes::Credits:
				RunCredits(scene, isNewScene); 
				auxPrevScene = Scenes::Credits;
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