#include "GameLoop.h"

#include "Raylib/header/raylib.h" 

#include "Scenes.h"
#include "Menu/Menu.h"
#include "Play/Play.h"
#include "Pause/Pause.h"
#include "Credits/Credits.h"

namespace FlappyBird
{
	static Scenes scene;
	static Music menuMusic;
	static Music gameMusic;

	static void InitProgram()
	{
		const int screenWidth = 1024;
		const int screenHeight = 768;

		InitWindow(screenWidth, screenHeight, "Flappy Viko");
		SetExitKey(NULL);
		
		InitAudioDevice();
		menuMusic = LoadMusicStream("res/AUDIO/music/menuMusic.mp3");
		gameMusic = LoadMusicStream("res/AUDIO/music/gameMusic.mp3");

		SetMusicVolume(menuMusic,0.2f);
		SetMusicVolume(gameMusic,0.2f);

		scene = Scenes::Menu;
	}

	void GameLoop()
	{
		InitProgram();
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
				RunMenu(scene, isNewScene, menuMusic);
				auxPrevScene = Scenes::Menu;
				break;

			case Scenes::Play:
				RunPlay(isNewScene, auxPrevScene, scene, gameMusic);
				auxPrevScene = Scenes::Play;
				break;

			case Scenes::Pause:
				RunPause(scene, isNewScene, gameMusic);
				auxPrevScene = Scenes::Pause;
				break;

			case Scenes::Credits:
				RunCredits(scene, isNewScene, menuMusic);
				auxPrevScene = Scenes::Credits;
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