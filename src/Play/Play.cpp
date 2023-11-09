#include "Play/Play.h"

#include "header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"

namespace FlappyBird
{
	static Player player;
	static Pipe pipe;

	void InitPlay()
	{
		player = InitPlayer();
		pipe = InitPipe();
	}

	void UpdatePlay()
	{
		UpdatePlayer(player);
		UpdatePipe(pipe);
	}

	void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawPipe(pipe);

		DrawPlayer(player);

		//DrawRectangle(500, 500, 100, 100, GREEN);

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