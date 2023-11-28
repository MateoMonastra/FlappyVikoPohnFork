#include "Menu/Menu.h"

#include "Button/Button.h"

namespace FlappyBird
{
	static Texture2D backTexture;

	static Texture2D playButtonTexture;
	static Texture2D creditsButtonTexture;
	static Texture2D exitButtonTexture;

	static Texture2D playButtonPressedTexture;
	static Texture2D creditsButtonPressedTexture;
	static Texture2D exitButtonPressedTexture;

	static Button playButton;
	static Button creditsButton;
	static Button exitButton;

	static void UnloadMenu()
	{
		UnloadTexture(backTexture);
		UnloadTexture(playButtonTexture);
		UnloadTexture(exitButtonTexture);
		UnloadTexture(creditsButtonTexture);
		UnloadTexture(playButtonPressedTexture);
		UnloadTexture(exitButtonPressedTexture);
		UnloadTexture(creditsButtonPressedTexture);
	}

	static void MenuInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), playButton))
		{
			playButton.isSelected = true;

			if (CheckMouseInput(playButton))
			{
				scene = Scenes::Play;
				UnloadMenu();
			}
		}
		else
			playButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), creditsButton))
		{
			creditsButton.isSelected = true;
			if (CheckMouseInput(creditsButton))
			{
				scene = Scenes::Credits;
				UnloadMenu();
			}
		}
		else
			creditsButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), exitButton))
		{
			exitButton.isSelected = true;
			if (CheckMouseInput(exitButton))
			{
				scene = Scenes::Exit;
				UnloadMenu();
			}
		}
		else
			exitButton.isSelected = false;
	}
	
	void InitMenu()
	{
		backTexture = LoadTexture("res/PNG/backmenu.png");
		InitMenuButtons();
	}

	void InitMenuButtons()
	{
		playButtonTexture = LoadTexture("res/PNG/playbutton.png");
		creditsButtonTexture = LoadTexture("res/PNG/creditsbutton.png");
		exitButtonTexture = LoadTexture("res/PNG/exitbutton.png");

		playButtonPressedTexture = LoadTexture("res/PNG/playbuttonpressed.png");
		creditsButtonPressedTexture = LoadTexture("res/PNG/creditsbuttonpressed.png");
		exitButtonPressedTexture = LoadTexture("res/PNG/exitbuttonpressed.png");

		const float buttonWidth = static_cast<float>(playButtonTexture.width);
		const float buttonHeight = static_cast<float>(playButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth / 2;
		const float buttonDistance = buttonHeight + 15;

		float playButtonY = static_cast<float>(GetScreenHeight()) / 2 - buttonHeight / 2;
		float creditsButtonY = playButtonY + buttonDistance;
		float exitButtonY = creditsButtonY + buttonDistance;

		Color buttonColor = RAYWHITE;

		InitButton(playButton, playButtonTexture, playButtonPressedTexture, buttonXPos, playButtonY, buttonWidth, buttonHeight, buttonColor);
		InitButton(creditsButton, creditsButtonTexture, creditsButtonPressedTexture, buttonXPos, creditsButtonY, buttonWidth, buttonHeight, buttonColor);
		InitButton(exitButton, exitButtonTexture, exitButtonPressedTexture, buttonXPos, exitButtonY, buttonWidth, buttonHeight, buttonColor);
	}

	void DrawMenu()
	{
		BeginDrawing();
		DrawTexture(backTexture, 0, 0, RAYWHITE);

		DrawButton(playButton);
		DrawButton(creditsButton);
		DrawButton(exitButton);
		EndDrawing();
	}


	void RunMenu(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitMenu();
		}

		DrawMenu();
		MenuInput(scene);
	}

}