#include "Play/Play.h"

#include "Raylib/header/raylib.h"

#include "Player/Player.h"
#include "Pipes/Pipe.h"
#include "Button/Button.h"
#include "Parallax/Parallax.h"
#include "Screen.h"

namespace FlappyBird
{
	static Player player1;
	static Player player2;
	static Pipe firstPipe;
	static Pipe secondPipe;

	static Button pauseButton;
	static Button pauseButtonPressed;

	static Button SinglePlayer;
	static Button MultiPlayer;

	static Texture2D loseTexture;

	static Button backMenuLoseButton;
	static Texture2D backMenuLoseButtonTexture;
	static Texture2D backMenuLoseButtonPressedTexture;
	
	static Button playAgainButton;
	static Texture2D playAgainButtonTexture;
	static Texture2D playAgainButtonPressedTexture;

	Parallax parallax;

	static Screen currentScreen;

	static void InputLoseScreen(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuLoseButton))
		{
			backMenuLoseButton.isSelected = true;

			if (CheckMouseInput(backMenuLoseButton))
			{
				scene = Scenes::Menu;
			}
		}
		else
			backMenuLoseButton.isSelected = false;

		if (CheckCollisionButtonMouse(GetMousePosition(), playAgainButton))
		{
			playAgainButton.isSelected = true;

			if (CheckMouseInput(playAgainButton))
			{
				InitPlay();
				currentScreen = Screen::ModeSelector;
				scene = Scenes::Play;
			}
		}
		else
			playAgainButton.isSelected = false;
	}

	static void InitLoseScreen()
	{
		loseTexture = LoadTexture("res/losescreen.png");

		backMenuLoseButtonTexture = LoadTexture("res/backmenubutton.png");
		playAgainButtonTexture = LoadTexture("res/playagain.png");
		backMenuLoseButtonPressedTexture = LoadTexture("res/backmenubuttonpressed.png");
		playAgainButtonPressedTexture = LoadTexture("res/playagainpressed.png");

		const float buttonWidth = static_cast<float>(backMenuLoseButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuLoseButtonTexture.height);
		float buttonYPos = static_cast<float>(GetScreenHeight()) / 4 * 3 - buttonHeight / 2;

		float backMenuPausebuttonXPos = static_cast<float>(GetScreenWidth()) / 2 - buttonWidth - 180;
		float playAgainButtonXPos = static_cast<float>(GetScreenWidth()) / 2 + buttonWidth + 40;

		InitButton(backMenuLoseButton, backMenuLoseButtonTexture, backMenuLoseButtonPressedTexture, backMenuPausebuttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
		InitButton(playAgainButton, playAgainButtonTexture, playAgainButtonPressedTexture, playAgainButtonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
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

	static void LoseCondition(Player player)
	{
		if (PlayerPipeCollision(firstPipe.topPosition, firstPipe.topHeight, player) || PlayerPipeCollision(firstPipe.botPosition, firstPipe.botHeight, player) ||
			PlayerPipeCollision(secondPipe.topPosition, secondPipe.topHeight, player) || PlayerPipeCollision(secondPipe.botPosition, secondPipe.botHeight, player))
		{
			currentScreen = Screen::Lose;
		}
	}

	static void UpdateScore(Player& player)
	{
		if (PlayerPipeCollision(firstPipe.midPosition,firstPipe.midHeight, player) && firstPipe.givePoints)
		{
			player.score += 1;
			firstPipe.givePoints = false;
		}
		if (PlayerPipeCollision(secondPipe.midPosition, secondPipe.midHeight, player) && secondPipe.givePoints)
		{
			player.score += 1;
			secondPipe.givePoints = false;
		}
	}
	
	static void UpdatePlay(Scenes& scene)
	{
		if (currentScreen == Screen::ModeSelector)
		{
			CheckModeSelectorInput();
		}
		else if (currentScreen == Screen::SinglePlayer)
		{
			if (IsMouseButtonUp(MOUSE_BUTTON_RIGHT))
			{
				UpdateParallax(parallax);
				CheckPauseInput(scene);
				UpdatePlayer(player1, player2, currentScreen);
				UpdatePipe(firstPipe);
				UpdatePipe(secondPipe);
				UpdateScore(player1);
				LoseCondition(player1);
			}
		}
		else if (currentScreen == Screen::MultiPlayer)
		{
			UpdateParallax(parallax);
			CheckPauseInput(scene);
			UpdatePlayer(player1, player2, currentScreen);
			UpdatePipe(firstPipe);
			UpdatePipe(secondPipe);
			UpdateScore(player1);
			UpdateScore(player2);
			LoseCondition(player1);
			LoseCondition(player2);
		}
		else if (currentScreen == Screen::Lose)
		{
			InputLoseScreen(scene);
		}
	}

	static void DrawPlay()
	{
		BeginDrawing();

		ClearBackground(BLACK);
	
		if (currentScreen == Screen::ModeSelector)
		{
			DrawButton(SinglePlayer);
			DrawButton(MultiPlayer);
		}
		else if (currentScreen == Screen::SinglePlayer)
		{
			DrawParallax(parallax);

			DrawPipe(firstPipe);

			DrawPipe(secondPipe);

			DrawPlayer(player1);

			DrawPlayerScore(player1);

			DrawButton(pauseButton);
		}
		else if (currentScreen == Screen::MultiPlayer)
		{
			DrawParallax(parallax);

			DrawPipe(firstPipe);

			DrawPipe(secondPipe);

			DrawPlayer(player1);

			DrawPlayer(player2);

			DrawPlayerScore(player1);

			DrawPlayerScore(player2);

			DrawButton(pauseButton);
		}
		else if (currentScreen == Screen::Lose)
		{
			DrawTexture(loseTexture, 0, 0, RAYWHITE);

			DrawButton(backMenuLoseButton);
			DrawButton(playAgainButton);

			int scoreX = GetScreenWidth() / 3;
			int scoreY = GetScreenHeight() / 3;
			int scoreFontSize = 50;

			DrawText(TextFormat("Total Score : %02i", player1.score), scoreX, scoreY, scoreFontSize, DARKPURPLE);
		}
		EndDrawing();
	}

	void InitPlay()
	{
		float pipeDistance = static_cast<float>(GetScreenWidth()) / 2.0f;
		float pipeWidth = 90.0f;
		float firstPipeX = static_cast<float>(GetScreenWidth());
		float secondPipeX = static_cast<float>(GetScreenWidth()) + pipeDistance + pipeWidth / 2;
		
		Texture2D player1Drop = LoadTexture("res/player1.png");
		Texture2D player1fly = LoadTexture("res/player1fly.png");

		Texture2D player2Drop = LoadTexture("res/player2.png");
		Texture2D player2fly = LoadTexture("res/player2fly.png");

		player1 = InitPlayer(player1Drop, player1fly);
		player2 = InitPlayer(player2Drop, player2fly);

		player1.scoreXPos = 10;
		player2.scoreXPos = GetScreenWidth() - 180;

		player1.scoreColor = BLUE;
		player2.scoreColor = RED;

		player2.topPosition.y -= 80;

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

		Texture2D SinglePlayerButtonTexture = LoadTexture("res/SinglePlayer.png");
		Texture2D SinglePlayerButtonPressedTexture = LoadTexture("res/SinglePlayer.png");

		const float SinglePlayerbuttonWidth = static_cast<float>(SinglePlayerButtonTexture.width);
		const float SinglePlayerbuttonHeight = static_cast<float>(SinglePlayerButtonTexture.height);
		float SinglePlayerbuttonXPos = static_cast<float>(GetScreenWidth() / 2) - 100;
		float SinglePlayerbuttonYPos = static_cast<float>(GetScreenHeight() / 2) - SinglePlayerbuttonHeight;
		
		InitButton(SinglePlayer, SinglePlayerButtonTexture, SinglePlayerButtonPressedTexture, SinglePlayerbuttonXPos, SinglePlayerbuttonYPos, SinglePlayerbuttonWidth, SinglePlayerbuttonHeight, RAYWHITE);

		Texture2D MultiPlayerButtonTexture = LoadTexture("res/MultiPlayer.png");
		Texture2D MultiPlayerButtonPressedTexture = LoadTexture("res/MultiPlayer.png");

		const float MultiPlayerbuttonWidth = static_cast<float>(MultiPlayerButtonTexture.width);
		const float MultiPlayerbuttonHeight = static_cast<float>(MultiPlayerButtonTexture.height);
		float MultiPlayerbuttonXPos = static_cast<float>(GetScreenWidth() / 2) + 100;
		float MultiPlayerbuttonYPos = static_cast<float>(GetScreenHeight() / 2) - MultiPlayerbuttonHeight;

		InitButton(MultiPlayer, MultiPlayerButtonTexture, MultiPlayerButtonPressedTexture, MultiPlayerbuttonXPos, MultiPlayerbuttonYPos, MultiPlayerbuttonWidth, MultiPlayerbuttonHeight, RAYWHITE);

		currentScreen = Screen::ModeSelector;

		InitLoseScreen();
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