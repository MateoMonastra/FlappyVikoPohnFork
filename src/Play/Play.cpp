#include "Play/Play.h"

#include "Raylib/header/raylib.h"

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

	bool PlayerPipeCollision()
	{
		float playerRightEdge = player.position.x + player.texture.width;
		float playerLeftEdge = player.position.x;
		float playerTopEdge = player.position.y + player.texture.height;
		float playerBottomEdge = player.position.y;

		float pipeRightEdge = pipe.position.x + pipe.width;
		float pipeLeftEdge = pipe.position.x;
		float pipeTopEdge = pipe.position.y + pipe.height;
		float pipeBottomEdge = pipe.position.y;

		return (playerRightEdge >= pipeLeftEdge &&
			playerLeftEdge <= pipeRightEdge &&
			playerTopEdge >= pipeBottomEdge &&
			playerBottomEdge <= pipeTopEdge);
	}

	void LoseCondition(Scenes& scene)
	{
		if (PlayerPipeCollision())
		{
			scene = Scenes::LoseScreen;
		}
	}

	void UpdatePlay(Scenes& scene)
	{
		UpdatePlayer(player, scene);
		UpdatePipe(pipe);
		LoseCondition(scene);
	}

	void DrawGameVersion()
	{
		int xPos = 10;
		int yPos = 10;
		int fontSize = 30;
		DrawText("Version 0.1", xPos, yPos, fontSize, RED);
	}

	void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawPipe(pipe);

		DrawPlayer(player);

		DrawGameVersion();

		EndDrawing();
	}

	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene)
	{
		if (isNewScene && previousScene != Scenes::Pause)
		{
			InitPlay();
		}

		UpdatePlay(scene);
		DrawPlay();
	}

}