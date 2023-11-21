#include "Pause.h"

#include "Raylib/header/raylib.h"

#include "Button/Button.h"

namespace FlappyBird
{
	static Texture2D pauseTexture;

	static Button resumeButton;
	static Button backMenuPauseButton;
	static Texture2D backMenuPauseButtonTexture;
	static Texture2D backMenuPauseButtonPressedTexture;
	static Texture2D resumeButtonTexture;
	static Texture2D resumeButtonPressedTexture;

	void InitPause()
	{
		pauseTexture = LoadTexture("res/pause.png");

		backMenuPauseButtonTexture = LoadTexture("res/backmenubutton.png");
		resumeButtonTexture = LoadTexture("res/resumebutton.png");

		backMenuPauseButtonPressedTexture = LoadTexture("res/backmenubuttonpressed.png");
		resumeButtonPressedTexture = LoadTexture("res/resumebuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuPauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuPauseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight - 10;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth - 180;
		float resumeButtonXPos = static_cast<float>(GetScreenWidth()) / 2 + buttonWidth + 40;

		InitButton(backMenuPauseButton, backMenuPauseButtonTexture, backMenuPauseButtonPressedTexture, backMenuPausebuttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(resumeButton, resumeButtonTexture, resumeButtonPressedTexture, resumeButtonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawPause()
	{
		BeginDrawing();

		DrawTexture(pauseTexture, 0, 0, RAYWHITE);

		DrawButton(backMenuPauseButton);
		DrawButton(resumeButton);

		EndDrawing();
	}

	void InputPause(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuPauseButton))
		{
			backMenuPauseButton.isSelected = true;

			if (CheckMouseInput(backMenuPauseButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuPauseButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), resumeButton))
		{
			resumeButton.isSelected = true;

			if (CheckMouseInput(resumeButton))
			{
				scene = Scenes::Play;
			}
		}
		else
			resumeButton.isSelected = false;
	}

	void RunPause(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitPause();
		}

		ShowCursor();

		DrawPause();
		InputPause(scene);
	}

}