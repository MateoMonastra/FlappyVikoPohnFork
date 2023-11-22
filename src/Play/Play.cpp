#include "Play/Play.h"

#include "Raylib/header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"
#include "Button/Button.h"
#include "Parallax/Parallax.h"

namespace FlappyBird
{
	static Player player;
	static Pipe firstPipe;
	static Pipe secondPipe;

	static Button pauseButton;
	static Button pauseButtonPressed;

	Parallax parallax;


	static void CheckPauseInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), pauseButton))
		{
			pauseButton.isSelected = true;

			if (CheckMouseInput(pauseButton))
			{
				scene = Scenes::Pause;
			}
		}
		else
			pauseButton.isSelected = false;
	}

	static bool PlayerPipeCollision(Vector2 pipePosition, float pipeHeight)
	{
		float playerRightEdge = player.topPosition.x + player.texture.width;
		float playerLeftEdge = player.topPosition.x;
		float playerTopEdge = player.topPosition.y + player.texture.height;
		float playerBottomEdge = player.topPosition.y;

		float pipeRightEdge = pipePosition.x + firstPipe.width;
		float pipeLeftEdge = pipePosition.x;
		float pipeTopEdge = pipePosition.y + pipeHeight;
		float pipeBottomEdge = pipePosition.y;

		return (playerRightEdge >= pipeLeftEdge &&
			playerLeftEdge <= pipeRightEdge &&
			playerTopEdge >= pipeBottomEdge &&
			playerBottomEdge <= pipeTopEdge);
	}

	static void LoseCondition(Scenes& scene)
	{
		if (PlayerPipeCollision(firstPipe.topPosition, firstPipe.topHeight) || PlayerPipeCollision(firstPipe.botPosition, firstPipe.botHeight) || 
			PlayerPipeCollision(secondPipe.topPosition, secondPipe.topHeight) || PlayerPipeCollision(secondPipe.botPosition, secondPipe.botHeight))
		{
			scene = Scenes::LoseScreen;
		}
	}

	static void UpdateScore()
	{
		if (PlayerPipeCollision(firstPipe.midPosition,firstPipe.midHeight) && firstPipe.givePoints)
		{
			player.score += 1;
			firstPipe.givePoints = false;
		}

		if (PlayerPipeCollision(secondPipe.midPosition, secondPipe.midHeight) && secondPipe.givePoints)
		{
			player.score += 1;
			secondPipe.givePoints = false;
		}
	}
	
	static void UpdatePlay(Scenes& scene)
	{
		UpdateParallax(parallax);
		CheckPauseInput(scene);
		UpdatePlayer(player, scene);
		UpdatePipe(firstPipe);
		UpdatePipe(secondPipe);
		UpdateScore();
		LoseCondition(scene);
	}

	static void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawParallax(parallax);

		DrawPipe(firstPipe);

		DrawPipe(secondPipe);

		DrawPlayer(player);

		DrawPlayerScore(player);

		DrawButton(pauseButton);

		EndDrawing();
	}

	void InitPlay()
	{
		float pipeDistance = static_cast<float>(GetScreenWidth()) / 2.0f;
		float pipeWidth = 90.0f;
		float firstPipeX = static_cast<float>(GetScreenWidth());
		float secondPipeX = static_cast<float>(GetScreenWidth()) + pipeDistance + pipeWidth / 2;
		
		player = InitPlayer();
		firstPipe = InitPipe(firstPipeX);
		secondPipe = InitPipe(secondPipeX);
		parallax = InitParallax();

		Texture2D pauseButtonTexture = LoadTexture("res/pausebutton.png");
		Texture2D pauseButtonPressedTexture = LoadTexture("res/pausebuttonpressed.png");

		const float buttonWidth = static_cast<float>(pauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(pauseButtonTexture.height);
		float buttonXPos = 20;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(pauseButton, pauseButtonTexture, pauseButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
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