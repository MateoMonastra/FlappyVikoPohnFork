#include "Player.h"

namespace FlappyBird
{
	Player InitPlayer()
	{
		Player player;

		player.textureDrop = LoadTexture("res/player2.png");
		player.textureFly = LoadTexture("res/player2fly.png");
		player.texture = player.textureDrop;

		float xPos = static_cast<float>(player.texture.width);
		float yPos = static_cast<float>(GetScreenHeight() / 2) - static_cast<float>(player.texture.height / 2);
		player.topPosition = { xPos, yPos};

		player.scale = 0.15f;
		
		player.dest.x = player.topPosition.x + static_cast<float>(player.texture.width) /2;
		player.dest.y = player.topPosition.y;
		player.dest.width = static_cast<float>(player.texture.width);
		player.dest.height = static_cast<float>(player.texture.height);

		player.source.width = static_cast<float>(player.texture.width);
		player.source.height = static_cast<float>(player.texture.height);
		player.source.x = 0;
		player.source.y = 0;

		player.origin = { player.dest.width / 2, player.dest.height / 2 };

		return player;
	}

	void UpdatePlayer(Player& player, Scenes& scene)
	{
		PlayerMovement(player);
		PlayerScreenCollision(player, scene);
		ChangeTexture(player);
	}

	void PlayerMovement(Player& player)
	{
		CheckMovementInput(player);

		player.velocity.y += player.gravity * GetFrameTime();
		player.topPosition.y += player.velocity.y * GetFrameTime();

		if (player.isJumping && player.velocity.y > 0)
		{
			player.isJumping = false;
		}
	}

	void CheckMovementInput(Player& player)
	{		
		if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			player.velocity.y = player.jumpForce;
			player.isJumping = true;
		}
	}

	void ChangeTexture(Player& player)
	{
		if (player.isJumping == true)
		{
			player.texture = player.textureFly;
		}
		else
		{
			player.texture = player.textureDrop;
		}
	}

	void PlayerScreenCollision(Player& player, Scenes& scene)
	{
		if (player.topPosition.y <= 0)
		{
			player.topPosition.y = 0;
			player.velocity.y = player.gravity * GetFrameTime();
		}

		if (player.topPosition.y >= GetScreenHeight())
		{
			scene = Scenes::LoseScreen;
		}

		int destFix = 30;
		player.dest.y = player.topPosition.y + destFix;
	}

	void DrawPlayer(Player player)
	{
		DrawTexturePro(player.texture, player.source, player.dest, player.origin, player.rotation, RAYWHITE);
		DrawRectangle(static_cast<int>(player.topPosition.x), static_cast<int>(player.topPosition.y), player.texture.width, player.texture.height, WHITE);
		
	}

	//static void UpdatePlayerScore()
	//{



	//}
}