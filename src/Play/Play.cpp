#include "Play/Play.h"

#include "Raylib/header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"
#include "Button/Button.h"
#include "Parallax/Parallax.h"

namespace FlappyBird
{
	static Player player;
	static Pipe pipe;

	static Button pauseButton;
	static Button pauseButtonPressed;

	Parallax parallax;

	void InitPlay()
	{
		player = InitPlayer();
		pipe = InitPipe();
		parallax = InitParallax();

		Texture2D pauseButtonTexture = LoadTexture("res/pausebutton.png");
		Texture2D pauseButtonPressedTexture = LoadTexture("res/pausebuttonpressed.png");

		const float buttonWidth = static_cast<float>(pauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(pauseButtonTexture.height);
		float buttonXPos = 20;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(pauseButton, pauseButtonTexture, pauseButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void CheckPauseInput(Scenes& scene)
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

	bool PlayerPipeCollision(Vector2 pipePosition, float pipeHeight)
	{
		float playerRightEdge = player.topPosition.x + player.texture.width;
		float playerLeftEdge = player.topPosition.x;
		float playerTopEdge = player.topPosition.y + player.texture.height;
		float playerBottomEdge = player.topPosition.y;

		float pipeRightEdge = pipePosition.x + pipe.width;
		float pipeLeftEdge = pipePosition.x;
		float pipeTopEdge = pipePosition.y + pipeHeight;
		float pipeBottomEdge = pipePosition.y;

		return (playerRightEdge >= pipeLeftEdge &&
			playerLeftEdge <= pipeRightEdge &&
			playerTopEdge >= pipeBottomEdge &&
			playerBottomEdge <= pipeTopEdge);
	}

	void LoseCondition(Scenes& scene)
	{
		if (PlayerPipeCollision(pipe.topPosition, pipe.topHeight) || PlayerPipeCollision(pipe.botPosition, pipe.botHeight))
		{
			scene = Scenes::LoseScreen;
		}
	}

	void UpdatePlay(Scenes& scene)
	{
		UpdateParallax(parallax);
		CheckPauseInput(scene);
		UpdatePlayer(player, scene);
		UpdatePipe(pipe);
		LoseCondition(scene);
	}

	void DrawGameVersion()
	{
		int xPos = 10;
		int yPos = 10;
		int fontSize = 30;
		DrawText("Version 0.2", xPos, yPos, fontSize, RED);
	}

	void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawParallax(parallax);

		DrawPipe(pipe);

		DrawPlayer(player);

		DrawGameVersion();

		DrawButton(pauseButton);

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