#include "Play/Play.h"

#include "Raylib/header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"
#include "Button/Button.h"

namespace FlappyBird
{
	static Player player;
	static Pipe pipe;

	static Button pauseButton;
	static Button pauseButtonPressed;

	void InitPlay()
	{
		player = InitPlayer();
		pipe = InitPipe();

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