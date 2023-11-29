#include "Pause.h"

#include "Button/Button.h"
#include "Play/Play.h"

namespace FlappyBird
{
	static Texture2D pauseTexture;

	static Button resumeButton;
	static Button backMenuPauseButton;
	static Texture2D backMenuPauseButtonTexture;
	static Texture2D backMenuPauseButtonPressedTexture;
	static Texture2D resumeButtonTexture;
	static Texture2D resumeButtonPressedTexture;

	static void UnloadPause()
	{
		UnloadTexture(pauseTexture);
		UnloadTexture(backMenuPauseButtonTexture);
		UnloadTexture(backMenuPauseButtonPressedTexture);
		UnloadTexture(resumeButtonTexture);
		UnloadTexture(resumeButtonPressedTexture);
		UnloadTexture(resumeButton.texture);
		UnloadTexture(backMenuPauseButton.texture);
	}

	void InitPause()
	{
		pauseTexture = LoadTexture("res/PNG/pause.png");

		backMenuPauseButtonTexture = LoadTexture("res/PNG/backmenubutton.png");
		resumeButtonTexture = LoadTexture("res/PNG/resumebutton.png");

		backMenuPauseButtonPressedTexture = LoadTexture("res/PNG/backmenubuttonpressed.png");
		resumeButtonPressedTexture = LoadTexture("res/PNG/resumebuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuPauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuPauseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight - 10;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth() / 2) - buttonWidth - 130;
		float resumeButtonXPos = static_cast<float>(GetScreenWidth() / 2) + buttonWidth - 130;

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
				UnloadPause();
				UnloadPlay();
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
				UnloadPause();
			}
		}
		else
			resumeButton.isSelected = false;
	}

	void RunPause(Scenes& scene, bool isNewScene, Music& music)
	{
		if (isNewScene)
		{
			InitPause();
			PlayMusicStream(music);
		}

		ShowCursor();
		UpdateMusicStream(music);
		DrawPause();
		InputPause(scene);
	}

}