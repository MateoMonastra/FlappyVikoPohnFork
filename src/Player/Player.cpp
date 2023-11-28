#include "Player.h"

#include "Play/Screen.h"

namespace FlappyBird
{
	double restStartAnimationTimer = GetTime();
	float animationTimerP1 = 0;
	float animationTimerP2 = 0;

	static void CheckMovementInput(Player& player1, Player& player2)
	{

		if (IsKeyPressed(KEY_W))
		{
			player1.velocity.y = player1.jumpForce;
			player1.isJumping = true;
		}

		if (IsKeyPressed(KEY_UP))
		{
			player2.velocity.y = player2.jumpForce;
			player2.isJumping = true;
		}
	}

	static void PlayerMovement(Player& player1, Player& player2)
	{
		CheckMovementInput(player1, player2);

		player1.velocity.y += player1.gravity * GetFrameTime();
		player1.topPosition.y += player1.velocity.y * GetFrameTime();

		player2.velocity.y += player2.gravity * GetFrameTime();
		player2.topPosition.y += player2.velocity.y * GetFrameTime();
	}


	static void PlayerScreenCollision(Player& player)
	{
		if (player.topPosition.y <= 0)
		{
			player.topPosition.y = 0;
			player.velocity.y = player.gravity * GetFrameTime();
		}

		if (player.topPosition.y >= GetScreenHeight())
		{
			player.isAlive = false;
		}

		player.dest.y = player.topPosition.y;

		player.hitBox.y = player.dest.y + player.dest.height / 3;
		player.hitBox.x = player.dest.x;
	}

	Player InitPlayer(Texture2D textureDrop, Texture2D textureFly)
	{
		Player player;

		player.textureDrop = textureDrop;
		player.textureFly = textureFly;
		player.texture = player.textureDrop;

		player.isAlive = true;

		player.scale = 0.15f;

		float xPos = static_cast<float>(GetScreenWidth()) / 2 - player.texture.width / static_cast<float>(2);;
		float yPos = static_cast<float>(GetScreenHeight() / 2) - static_cast<float>(player.texture.height * player.scale) / 2;
		player.topPosition = { xPos, yPos };

		
		player.dest.x = player.topPosition.x;
		player.dest.y = player.topPosition.y;
		player.dest.width = static_cast<float>(player.texture.width * player.scale);
		player.dest.height = static_cast<float>(player.texture.height * player.scale);

		player.source.width = static_cast<float>(player.texture.width);
		player.source.height = static_cast<float>(player.texture.height);
		player.source.x = 0;
		player.source.y = 0;

		player.origin = { (player.dest.width * player.scale) / 2, (player.dest.height * player.scale) / 2 };

		int hitBoxFixer = 10;
		player.hitBox = { player.dest.x, player.dest.y + player.dest.height / 3 , player.dest.width - hitBoxFixer, player.dest.height/4 };

		return player;
	}

	void UpdatePlayer(Player& player1, Player& player2, Screen& currentScreen)
	{
		PlayerMovement(player1, player2);

		PlayerScreenCollision(player1);

		ChangeTexture(player1, animationTimerP1);

		if (currentScreen == Screen::MultiPlayer)
		{
			PlayerScreenCollision(player2);

			ChangeTexture(player2, animationTimerP2);
		}

	}

	void DrawPlayer(Player player)
	{
		if (player.isAlive)
		{
			DrawTexturePro(player.texture, player.source, player.dest, player.origin, player.rotation, RAYWHITE);
		}
	}

	void DrawPlayerScore(Player player, Font font)
	{
		Vector2 textPos = { static_cast<float>(GetScreenWidth()) / 2 - 80, 10 };
		float fontSize = 50;
		float textSpacing = 5;
		DrawTextEx(font, TextFormat("Score: %01i", player.score), textPos, fontSize, textSpacing, DARKBROWN);
	}

	void ChangeTexture(Player& player, float& animationTimer)
	{
		const float animationCooldown = 0.3f;

		animationTimer += GetFrameTime();

		if (player.isJumping)
		{
			if (animationTimer >= animationCooldown)
			{
				player.texture = player.textureFly;
			}

			animationTimer = 0;
			player.isJumping = false;
		}
		else if (animationTimer >= animationCooldown)
		{
			player.texture = player.textureDrop;
		}
	}

	void RestStartAnimation(Player& player1, Player& player2)
	{
		ChangeTexture(player1,animationTimerP1);
		ChangeTexture(player2,animationTimerP2);

		int animationCoolDown = 1;

		if (GetTime() - restStartAnimationTimer > animationCoolDown)
		{
			if (player1.isJumping)
			{
				player1.isJumping = false;
				player2.isJumping = false;
			}
			else
			{
				player1.isJumping = true;
				player2.isJumping = true;
			}
			restStartAnimationTimer = GetTime();
		}
	}
}