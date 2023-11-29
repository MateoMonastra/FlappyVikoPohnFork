#include "Menu/Menu.h"

#include "Button/Button.h"

namespace FlappyBird
{
	static Texture2D backTexture;
	static Texture2D title;

	static Texture2D playButtonTexture;
	static Texture2D creditsButtonTexture;
	static Texture2D exitButtonTexture;

	static Texture2D playButtonPressedTexture;
	static Texture2D creditsButtonPressedTexture;
	static Texture2D exitButtonPressedTexture;

	static Button playButton;
	static Button creditsButton;
	static Button exitButton;

	static Sound birdScream;
	static Sound buttonPress;

	float titleY = 0;
	bool soundWasPlayed = false;

	static void UpdateTitlePos()
	{
		int titleFinalPosY = -150;

		if (titleY > titleFinalPosY)
		{
			int titleSpeed = 200;

			titleY -= titleSpeed * GetFrameTime();
		}
		else if (!soundWasPlayed)
		{
			PlaySound(birdScream);
			soundWasPlayed = true;
		}
	
	}

	static void UnloadMenu()
	{
		UnloadTexture(backTexture);
		UnloadTexture(title);

		UnloadTexture(creditsButtonTexture);
		UnloadTexture(creditsButtonPressedTexture);
		
		UnloadTexture(playButtonTexture);
		UnloadTexture(playButtonPressedTexture);
		
		UnloadTexture(exitButtonTexture);
		UnloadTexture(exitButtonPressedTexture);

		UnloadSound(birdScream);
		UnloadSound(buttonPress);
	}

	static void MenuInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), playButton))
		{
			playButton.isSelected = true;

			if (CheckMouseInput(playButton))
			{
				PlaySound(buttonPress);
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
				PlaySound(buttonPress);
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
				PlaySound(buttonPress);
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
		title = LoadTexture("res/PNG/title.png");

		birdScream = LoadSound("res/AUDIO/sounds/birdScream.mp3");
		buttonPress = LoadSound("res/AUDIO/sounds/buttonSound.mp3");

		SetSoundVolume(buttonPress, 0.2f);

		titleY = static_cast<float>(GetScreenHeight());
		InitMenuButtons();

		soundWasPlayed = false;
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
		const float buttonDistance = buttonHeight + 35;

		float playButtonY = static_cast<float>(GetScreenHeight()) / 2 ;
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

		int titleX = GetScreenWidth() / 2 - title.width /2;
		DrawTexture(title, titleX, static_cast<int>(titleY),WHITE);
		
		DrawButton(playButton);
		DrawButton(creditsButton);
		DrawButton(exitButton);
		
		EndDrawing();
	}

	void RunMenu(Scenes& scene, bool isNewScene, Music& music)
	{
		if (isNewScene)
		{
			InitMenu();
			PlayMusicStream(music);
		}
		UpdateTitlePos();
		UpdateMusicStream(music);
		DrawMenu();
		MenuInput(scene);
	}
}