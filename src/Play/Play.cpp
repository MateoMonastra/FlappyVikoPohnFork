#include "Play/Play.h"

#include "Raylib/header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"
#include "Button/Button.h"
#include "Parallax/Parallax.h"
#include "Screen.h"
#include <iostream>

namespace FlappyBird
{
	static Player player1;
	static Player player2;

	static Pipe firstPipe;
	static Pipe secondPipe;
	static Pipe thirdPipe;

	static Button pauseButton;

	static Texture2D modeSelectorBack;
	static Button SinglePlayer;
	static Button MultiPlayer;

	static Texture2D Rules;
	static Button Next;
	static Button Menu;

	static Texture2D loseTexture_Bad;
	static Texture2D loseTexture_Ok;
	static Texture2D loseTexture_Good;
	static Texture2D loseTexture_VeryGood;

	static Button backMenuLoseButton;
	static Texture2D backMenuLoseButtonTexture;
	static Texture2D backMenuLoseButtonPressedTexture;

	static Button playAgainButton;
	static Texture2D playAgainButtonTexture;
	static Texture2D playAgainButtonPressedTexture;

	static Parallax parallax;

	static Font textFont;

	static Screen currentScreen;

	static Sound celebration;

	static bool celebrationWasPlayed = false;

	bool GAME_OVER = false;

	bool restStart = {};

	bool reverseMode = false;

	static int score_Ok = 10;
	static int score_Good = 20;
	static int score_VeryGood = 35;

	static void RestStart()
	{
		RestStartAnimation(player1, player2);

		if (currentScreen == Screen::MultiPlayer)
		{
			if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
			{
				restStart = false;
				player1.isJumping = false;
				player2.isJumping = false;
			}
		}
		else
		{
			if (IsKeyPressed(KEY_W))
			{
				restStart = false;
				player1.isJumping = false;
			}
		}
	}

	static void InitRules()
	{
		Rules = LoadTexture("res/PNG/rules.png");

		Texture2D MenuTexture = LoadTexture("res/PNG/backmenubutton.png");
		Texture2D MenuPressedTexture = LoadTexture("res/PNG/backmenubuttonpressed.png");

		Texture2D NextTexture = LoadTexture("res/PNG/next.png");
		Texture2D NextPressedTexture = LoadTexture("res/PNG/nextpressed.png");

		const float buttonWidth = static_cast<float>(MenuTexture.width);
		const float buttonHeight = static_cast<float>(MenuTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 4 * 3 + buttonHeight;

		float MenuXPos = static_cast<float>(GetScreenWidth() / 2) - buttonWidth - 140;
		float NextXPos = static_cast<float>(GetScreenWidth() / 2) + buttonWidth - 130;

		InitButton(Menu, MenuTexture, MenuPressedTexture, MenuXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(Next, NextTexture, NextPressedTexture, NextXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);

	}

	static void InitGame()
	{
		Texture2D player1Drop = LoadTexture("res/PNG/player1.png");
		Texture2D player1fly = LoadTexture("res/PNG/player1fly.png");

		Texture2D player2Drop = LoadTexture("res/PNG/player2.png");
		Texture2D player2fly = LoadTexture("res/PNG/player2fly.png");

		player1 = InitPlayer(player1Drop, player1fly);
		player2 = InitPlayer(player2Drop, player2fly);

		player2.topPosition.y -= 80;
		player2.dest.y = player2.topPosition.y;

		float pipeDistance = static_cast<float>(GetScreenWidth()) / 2.0f;
		float pipeWidth = 90.0f;
		float firstPipeX = static_cast<float>(GetScreenWidth());
		float secondPipeX = static_cast<float>(GetScreenWidth()) + pipeDistance + pipeWidth / 2;
		float thirdPipeX = 0 - pipeWidth;

		firstPipe = InitPipe(firstPipeX);
		secondPipe = InitPipe(secondPipeX);
		thirdPipe = InitPipe(thirdPipeX);

		parallax = InitParallax();

		Texture2D pauseButtonTexture = LoadTexture("res/PNG/pausebutton.png");
		Texture2D pauseButtonPressedTexture = LoadTexture("res/PNG/pausebuttonpressed.png");

		const float buttonWidth = static_cast<float>(pauseButtonTexture.width);
		const float buttonHeight = static_cast<float>(pauseButtonTexture.height);
		float buttonXPos = 20;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(pauseButton, pauseButtonTexture, pauseButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	static void InitModeSelector()
	{

		Texture2D SinglePlayerButtonTexture = LoadTexture("res/PNG/SinglePlayer.png");
		Texture2D SinglePlayerButtonPressedTexture = LoadTexture("res/PNG/SinglePlayerpressed.png");

		const float SinglePlayerbuttonWidth = static_cast<float>(SinglePlayerButtonTexture.width);
		const float SinglePlayerbuttonHeight = static_cast<float>(SinglePlayerButtonTexture.height);
		float SinglePlayerbuttonXPos = static_cast<float>(GetScreenWidth() / 3) - SinglePlayerbuttonWidth;
		float SinglePlayerbuttonYPos = static_cast<float>(GetScreenHeight() / 2) - SinglePlayerbuttonHeight;

		InitButton(SinglePlayer, SinglePlayerButtonTexture, SinglePlayerButtonPressedTexture, SinglePlayerbuttonXPos, SinglePlayerbuttonYPos, SinglePlayerbuttonWidth, SinglePlayerbuttonHeight, RAYWHITE);

		Texture2D MultiPlayerButtonTexture = LoadTexture("res/PNG/MultiPlayer.png");
		Texture2D MultiPlayerButtonPressedTexture = LoadTexture("res/PNG/MultiPlayerpressed.png");

		const float MultiPlayerbuttonWidth = static_cast<float>(MultiPlayerButtonTexture.width);
		const float MultiPlayerbuttonHeight = static_cast<float>(MultiPlayerButtonTexture.height);
		float MultiPlayerbuttonXPos = static_cast<float>(GetScreenWidth() / 3) * 2;
		float MultiPlayerbuttonYPos = static_cast<float>(GetScreenHeight() / 2) - MultiPlayerbuttonHeight;

		InitButton(MultiPlayer, MultiPlayerButtonTexture, MultiPlayerButtonPressedTexture, MultiPlayerbuttonXPos, MultiPlayerbuttonYPos, MultiPlayerbuttonWidth, MultiPlayerbuttonHeight, RAYWHITE);

		modeSelectorBack = LoadTexture("res/PNG/ModeSelectorBack.png");
	}

	static void InitLoseScreen()
	{
		loseTexture_Bad = LoadTexture("res/PNG/losescreen_Bad.png");
		loseTexture_Ok = LoadTexture("res/PNG/losescreen_ItsOk.png");
		loseTexture_Good = LoadTexture("res/PNG/losescreen_WellDone.png");
		loseTexture_VeryGood = LoadTexture("res/PNG/losescreen_Amazing.png");

		backMenuLoseButtonTexture = LoadTexture("res/PNG/backmenubutton.png");
		playAgainButtonTexture = LoadTexture("res/PNG/playagain.png");
		backMenuLoseButtonPressedTexture = LoadTexture("res/PNG/backmenubuttonpressed.png");
		playAgainButtonPressedTexture = LoadTexture("res/PNG/playagainpressed.png");

		const float buttonWidth = static_cast<float>(backMenuLoseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuLoseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 4 * 3 + buttonHeight;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth() / 2) - buttonWidth - 130;
		float playAgainButtonXPos = static_cast<float>(GetScreenWidth() / 2) + buttonWidth - 130;

		InitButton(backMenuLoseButton, backMenuLoseButtonTexture, backMenuLoseButtonPressedTexture, backMenuPausebuttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(playAgainButton, playAgainButtonTexture, playAgainButtonPressedTexture, playAgainButtonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	static void CheckLoseScreenInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuLoseButton))
		{
			backMenuLoseButton.isSelected = true;

			if (CheckMouseInput(backMenuLoseButton))
			{
				scene = Scenes::Menu;
				UnloadPlay();
			}
		}
		else
			backMenuLoseButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), playAgainButton))
		{
			playAgainButton.isSelected = true;

			if (CheckMouseInput(playAgainButton))
			{
				currentScreen = Screen::Rules;
				scene = Scenes::Play;
				UnloadPlay();
				InitPlay();
			}
		}
		else
			playAgainButton.isSelected = false;
	}

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

		if (IsKeyPressed(KEY_ESCAPE))
		{
			scene = Scenes::Pause;
		}
	}

	static void CheckRulesInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), Next))
		{
			Next.isSelected = true;

			if (CheckMouseInput(Next))
			{
				currentScreen = Screen::ModeSelector;
			}
		}
		else
			Next.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), Menu))
		{
			Menu.isSelected = true;

			if (CheckMouseInput(Menu))
			{
				scene = Scenes::Menu;
				UnloadPlay();
			}
		}
		else
			Menu.isSelected = false;
	}

	static void CheckModeSelectorInput()
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), SinglePlayer))
		{
			SinglePlayer.isSelected = true;

			if (CheckMouseInput(SinglePlayer))
			{
				currentScreen = Screen::SinglePlayer;
			}
		}
		else
			SinglePlayer.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), MultiPlayer))
		{
			MultiPlayer.isSelected = true;

			if (CheckMouseInput(MultiPlayer))
			{
				currentScreen = Screen::MultiPlayer;
			}
		}
		else
			MultiPlayer.isSelected = false;
	}

	static bool PlayerPipeCollision(Vector2 pipePosition, float pipeHeight, Player player)
	{
		float playerRightEdge = player.hitBox.x + player.hitBox.width;
		float playerLeftEdge = player.hitBox.x;
		float playerTopEdge = player.hitBox.y + player.hitBox.height;
		float playerBottomEdge = player.hitBox.y;

		float pipeRightEdge = pipePosition.x + firstPipe.width;
		float pipeLeftEdge = pipePosition.x;
		float pipeTopEdge = pipePosition.y + pipeHeight;
		float pipeBottomEdge = pipePosition.y;

		return (playerRightEdge >= pipeLeftEdge &&
			playerLeftEdge <= pipeRightEdge &&
			playerTopEdge >= pipeBottomEdge &&
			playerBottomEdge <= pipeTopEdge);
	}

	static void LoseCondition(Player& player)
	{
		if (player.isAlive)
		{
			if (PlayerPipeCollision(firstPipe.topPosition, firstPipe.topHeight, player) || PlayerPipeCollision(firstPipe.botPosition, firstPipe.botHeight, player) ||
				PlayerPipeCollision(secondPipe.topPosition, secondPipe.topHeight, player) || PlayerPipeCollision(secondPipe.botPosition, secondPipe.botHeight, player) ||
				PlayerPipeCollision(thirdPipe.topPosition, thirdPipe.topHeight, player) || PlayerPipeCollision(thirdPipe.botPosition, thirdPipe.botHeight, player))
			{
				player.isAlive = false;
				PlaySound(player.crash);
			}
		}

		if (currentScreen == Screen::SinglePlayer && !player1.isAlive)
		{
			GAME_OVER = true;
		}

		if (currentScreen == Screen::MultiPlayer && !player1.isAlive && !player2.isAlive)
		{
			GAME_OVER = true;
		}
	}

	static void UpdateScore(Player& player)
	{
		if (PlayerPipeCollision(firstPipe.midPosition, firstPipe.midHeight, player) && firstPipe.givePoints)
		{
			player1.score += 1;
			firstPipe.givePoints = false;
		}
		if (PlayerPipeCollision(secondPipe.midPosition, secondPipe.midHeight, player) && secondPipe.givePoints)
		{
			player1.score += 1;
			secondPipe.givePoints = false;
		}
	}

	static void UpdatePlay(Scenes& scene)
	{
		if (currentScreen == Screen::Rules)
		{
			CheckRulesInput(scene);
		}
		else if (currentScreen == Screen::ModeSelector)
		{
			CheckModeSelectorInput();
		}
		else if (currentScreen == Screen::SinglePlayer && !GAME_OVER)
		{

			UpdateParallax(parallax);
			CheckPauseInput(scene);

			if (!restStart)
			{
				UpdatePlayer(player1, player2, currentScreen);
				UpdatePipe(firstPipe);
				UpdatePipe(secondPipe);
				UpdateScore(player1);
				LoseCondition(player1);

				if (player1.score == 25 && !reverseMode)
				{
					reverseMode = true;
					StartReversePhasePipe(firstPipe, secondPipe, thirdPipe);
				}
				if (reverseMode)
				{
					if (secondPipe.topPosition.x < firstPipe.topPosition.x)
					{
						UpdatePipeReverse(thirdPipe, firstPipe);
					}
					else
					{
						UpdatePipeReverse(thirdPipe, secondPipe);
					}
				}
			}
			else
			{
				RestStart();
			}
		}
		else if (currentScreen == Screen::MultiPlayer && !GAME_OVER)
		{

			UpdateParallax(parallax);
			CheckPauseInput(scene);

			if (!restStart)
			{
				UpdatePlayer(player1, player2, currentScreen);
				UpdatePipe(firstPipe);
				UpdatePipe(secondPipe);
				UpdateScore(player1);
				UpdateScore(player2);
				LoseCondition(player1);
				LoseCondition(player2);

				if (player1.score == 5 && !reverseMode)
				{
					reverseMode = true;
					StartReversePhasePipe(firstPipe, secondPipe, thirdPipe);
				}
				if (reverseMode)
				{
					if (secondPipe.topPosition.x < firstPipe.topPosition.x)
					{
						UpdatePipeReverse(thirdPipe, firstPipe);
					}
					else
					{
						UpdatePipeReverse(thirdPipe, secondPipe);
					}
				}
			}
			else
			{
				RestStart();
			}

		}
		else
		{
			if (player1.score > score_VeryGood && !celebrationWasPlayed)
			{
				PlaySound(celebration);
				celebrationWasPlayed = true;
			}

			CheckLoseScreenInput(scene);
		}
	}

	static void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		if (currentScreen == Screen::Rules)
		{
			DrawTexture(Rules, 0, 0, WHITE);

			DrawButton(Menu);

			DrawButton(Next);
		}
		else if (currentScreen == Screen::ModeSelector)
		{
			DrawTexture(modeSelectorBack, 0, 0, WHITE);
			DrawButton(SinglePlayer);
			DrawButton(MultiPlayer);
		}
		else if (currentScreen == Screen::SinglePlayer)
		{
			DrawParallax(parallax);

			DrawPipe(firstPipe);

			DrawPipe(secondPipe);

			DrawPipe(thirdPipe);

			DrawPlayer(player1);


			if (restStart)
			{
				Vector2 textPos = { static_cast<float>(GetScreenWidth()) / 6, static_cast<float>(GetScreenHeight()) / 5 };
				float textFontSize = 90;
				float textSpacing = 20;
				DrawTextEx(textFont, "Jump to begin!", textPos, textFontSize, textSpacing, WHITE);
			}
			if (GAME_OVER)
			{
				Vector2 loseTexturePos = { static_cast<float>(GetScreenWidth() / 4), static_cast<float>(GetScreenHeight() / 4) };
				float loseTextureScale = 0.5f;

				if (player1.score < score_Ok)
				{
					DrawTextureEx(loseTexture_Bad, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else if (player1.score < score_Good)
				{
					DrawTextureEx(loseTexture_Ok, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else if (player1.score < score_VeryGood)
				{
					DrawTextureEx(loseTexture_Good, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else
				{
					DrawTextureEx(loseTexture_VeryGood, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}

				DrawButton(backMenuLoseButton);
				DrawButton(playAgainButton);

				Vector2 scorePos = { static_cast<float>(GetScreenWidth()) / 3 - 50, static_cast<float>(GetScreenHeight()) / 3 + 50 };
				if (player1.score >= score_Ok)
				{
					scorePos = { static_cast<float>(GetScreenWidth()) / 3 - 70, static_cast<float>(GetScreenHeight()) / 3 + 50 };
				}

				float scoreFontSize = 90;
				float textSpacing = 5;

				DrawTextEx(textFont, TextFormat("Total Score : %01i", player1.score), scorePos, scoreFontSize, textSpacing, DARKBROWN);
			}
			else
			{
				DrawPlayerScore(player1, textFont);
				DrawButton(pauseButton);
			}
		}
		else if (currentScreen == Screen::MultiPlayer)
		{
			DrawParallax(parallax);

			DrawPipe(firstPipe);

			DrawPipe(secondPipe);

			DrawPipe(thirdPipe);

			DrawPlayer(player1);

			DrawPlayer(player2);


			if (restStart)
			{
				Vector2 textPos = { static_cast<float>(GetScreenWidth()) / 6, static_cast<float>(GetScreenHeight()) / 5 };
				float textFontSize = 90;
				float textSpacing = 20;
				DrawTextEx(textFont, "Jump to begin!", textPos, textFontSize, textSpacing, WHITE);
			}
			if (GAME_OVER)
			{
				Vector2 loseTexturePos = { static_cast<float>(GetScreenWidth() / 4), static_cast<float>(GetScreenHeight() / 4) };
				float loseTextureScale = 0.5f;

				if (player1.score < score_Ok)
				{
					DrawTextureEx(loseTexture_Bad, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else if (player1.score < score_Good)
				{
					DrawTextureEx(loseTexture_Ok, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else if (player1.score < score_VeryGood)
				{
					DrawTextureEx(loseTexture_Good, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}
				else
				{
					DrawTextureEx(loseTexture_VeryGood, loseTexturePos, 0, loseTextureScale, RAYWHITE);
				}


				DrawButton(backMenuLoseButton);
				DrawButton(playAgainButton);

				Vector2 scorePos = { static_cast<float>(GetScreenWidth()) / 3 - 50, static_cast<float>(GetScreenHeight()) / 3 + 50 };
				if (player1.score >= score_Ok)
				{
					scorePos = { static_cast<float>(GetScreenWidth()) / 3 - 70, static_cast<float>(GetScreenHeight()) / 3 + 50 };
				}

				float scoreFontSize = 90;
				float textSpacing = 5;

				DrawTextEx(textFont, TextFormat("Total Score : %01i", player1.score), scorePos, scoreFontSize, textSpacing, DARKBROWN);
			}
			else
			{
				DrawPlayerScore(player1, textFont);
				DrawButton(pauseButton);
			}
		}
		EndDrawing();
	}

	void InitPlay()
	{
		currentScreen = Screen::Rules;

		InitRules();

		InitGame();

		InitModeSelector();

		InitLoseScreen();

		GAME_OVER = false;

		restStart = true;

		reverseMode = false;

		int fontSize = 90;

		textFont = LoadFontEx("res/Acme-Regular.ttf", fontSize, NULL, NULL);

		celebration = LoadSound("res/AUDIO/sounds/celebration.mp3");

		SetSoundVolume(celebration, 0.2f);
		celebrationWasPlayed = false;
	}

	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene, Music& music)
	{
		if (isNewScene && previousScene != Scenes::Pause)
		{
			InitPlay();

			PlayMusicStream(music);
		}

		UpdateMusicStream(music);
		DrawPlay();
		UpdatePlay(scene);
	}

	void UnloadPlay()
	{
		UnloadTexture(player1.textureDrop);
		UnloadTexture(player1.textureFly);
		UnloadTexture(player2.textureDrop);
		UnloadTexture(player2.textureFly);

		UnloadTexture(firstPipe.texture);
		UnloadTexture(secondPipe.texture);
		UnloadTexture(thirdPipe.texture);

		UnloadTexture(pauseButton.texture);
		UnloadTexture(pauseButton.texturePressed);

		UnloadTexture(modeSelectorBack);

		UnloadTexture(SinglePlayer.texture);
		UnloadTexture(SinglePlayer.texturePressed);

		UnloadTexture(MultiPlayer.texture);
		UnloadTexture(MultiPlayer.texturePressed);

		UnloadTexture(Rules);

		UnloadTexture(Next.texture);
		UnloadTexture(Next.texturePressed);
		UnloadTexture(Menu.texture);
		UnloadTexture(Menu.texturePressed);

		UnloadTexture(loseTexture_Bad);
		UnloadTexture(loseTexture_Ok);
		UnloadTexture(loseTexture_Good);
		UnloadTexture(loseTexture_VeryGood);

		UnloadTexture(backMenuLoseButtonTexture);
		UnloadTexture(backMenuLoseButtonPressedTexture);
		UnloadTexture(backMenuLoseButton.texture);
		UnloadTexture(backMenuLoseButton.texturePressed);

		UnloadTexture(playAgainButtonTexture);
		UnloadTexture(playAgainButtonPressedTexture);
		UnloadTexture(playAgainButton.texture);
		UnloadTexture(playAgainButton.texturePressed);

		UnloadTexture(parallax.backTexture);
		UnloadTexture(parallax.middleTexture);
		UnloadTexture(parallax.frontTexture);

		UnloadSound(player1.crash);
		UnloadSound(player1.fall);
		UnloadSound(player1.jump);

		UnloadSound(player2.crash);
		UnloadSound(player2.fall);
		UnloadSound(player2.jump);
		UnloadSound(celebration);

		UnloadFont(textFont);
	}

}