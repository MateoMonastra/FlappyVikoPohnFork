#include "Player.h"

#include "Play/Screen.h"

namespace FlappyBird
{
	float animationTimer = 0;

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

		if (player1.score >= 2)
		{
			player1.topPosition.x = static_cast<float>(GetScreenWidth()) / 2 - player1.texture.width / 2;
			player1.dest.x = player1.topPosition.x;
		}
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

		int destFix = 30;
		player.dest.y = player.topPosition.y + destFix;
	}

	Player InitPlayer(Texture2D textureDrop, Texture2D textureFly)
	{
		Player player;

		player.textureDrop = textureDrop;
		player.textureFly = textureFly;
		player.texture = player.textureDrop;

		player.isAlive = true;

		player.scale = 0.5f;

		float xPos = static_cast<float>(player.texture.width * player.scale);
		float yPos = static_cast<float>(GetScreenHeight() / 2) - static_cast<float>(player.texture.height * player.scale) / 2;
		player.topPosition = { xPos, yPos };


		player.dest.x = player.topPosition.x + static_cast<float>(player.texture.width * player.scale) / 2;
		player.dest.y = player.topPosition.y;
		player.dest.width = static_cast<float>(player.texture.width * player.scale);
		player.dest.height = static_cast<float>(player.texture.height * player.scale);

		player.source.width = static_cast<float>(player.texture.width);
		player.source.height = static_cast<float>(player.texture.height);
		player.source.x = 0;
		player.source.y = 0;

		player.origin = { (player.dest.width * player.scale) / 2, (player.dest.height * player.scale) / 2 };

		return player;
	}

	void UpdatePlayer(Player& player1, Player& player2, Screen& currentScreen)
	{
		PlayerMovement(player1, player2);

		PlayerScreenCollision(player1);

		ChangeTexture(player1);

		if (currentScreen == Screen::MultiPlayer)
		{
			PlayerScreenCollision(player2);
			ChangeTexture(player2);
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
		DrawTextEx(font, TextFormat("Score: %01i", player.score), textPos, fontSize, textSpacing, DARKPURPLE);
	}

	void ChangeTexture(Player& player)
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
}