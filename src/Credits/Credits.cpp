#include "Credits.h"

#include "Raylib/header/raylib.h"

#include "Button/Button.h"

namespace FlappyBird
{
	static Texture2D creditsTexture;

	static Button backMenuCreditsButton;
	static Texture2D backMenuCreditsButtonTexture;
	static Texture2D backMenuCreditsButtonPressedTexture;

	static void UnloadCredits()
	{
		UnloadTexture(creditsTexture);
		UnloadTexture(backMenuCreditsButtonTexture);
		UnloadTexture(backMenuCreditsButtonPressedTexture);
	
	}

	static void CreditsInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuCreditsButton))
		{
			backMenuCreditsButton.isSelected = true;

			if (CheckMouseInput(backMenuCreditsButton))
			{
				UnloadCredits();
				scene = Scenes::Menu;
			}
		}
		else
			backMenuCreditsButton.isSelected = false;
	}
	
	void InitCredits()
	{
		creditsTexture = LoadTexture("res/PNG/credits.png");
		backMenuCreditsButtonTexture = LoadTexture("res/PNG/backmenubutton.png");
		backMenuCreditsButtonPressedTexture = LoadTexture("res/PNG/backmenubuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuCreditsButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuCreditsButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuCreditsButton, backMenuCreditsButtonTexture, backMenuCreditsButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawCredits()
	{
		BeginDrawing();

		DrawTexture(creditsTexture, 0, 0, RAYWHITE);
		DrawButton(backMenuCreditsButton);

		EndDrawing();
	}

	void RunCredits(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitCredits();
		}

		DrawCredits();
		CreditsInput(scene);
	}
}