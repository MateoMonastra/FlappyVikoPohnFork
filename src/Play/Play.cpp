#include "Play/Play.h"

#include "header/raylib.h"

#include "Player/Player.h"

namespace FlappyBird
{
	static Player player;

	void InitPlay()
	{
		player = InitPlayer();
	}

	void UpdatePlay()
	{
		UpdatePlayer(player);
	}

	void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawPlayer(player);

		EndDrawing();
	}

	void RunPlay(bool isNewScene, Scenes previousScene)
	{
		if (isNewScene && previousScene != Scenes::Pause)
		{
			InitPlay();
		}

		UpdatePlay();
		DrawPlay();
	}

}