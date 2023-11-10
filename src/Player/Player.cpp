#include "Player.h"

namespace FlappyBird
{
	Player InitPlayer()
	{
		Player player;

		player.speed = 700.0f;

		player.texture = LoadTexture("res/player2.png");

		float xPos = static_cast<float>(player.texture.width);
		float yPos = static_cast<float>(GetScreenHeight() / 2) - static_cast<float>(player.texture.height / 2);
		player.position = { xPos, yPos};

		player.scale = 0.15f;
		
		player.dest.x = player.position.x;
		player.dest.y = player.position.y;
		player.dest.width = static_cast<float>(player.texture.width) * player.scale;
		player.dest.height = static_cast<float>(player.texture.height) * player.scale;

		player.source.width = static_cast<float>(player.texture.width);
		player.source.height = static_cast<float>(player.texture.height);
		player.source.x = 0;
		player.source.y = 0;

		player.origin = { player.dest.width / 2, player.dest.height / 2 };

		return player;
	}

	void UpdatePlayer(Player& player)
	{
		PlayerMovement(player);
		PlayerScreenCollision(player);
	}

	void PlayerMovement(Player& player)
	{
		CheckMovementInput(player);

		player.velocity.y += player.gravity * GetFrameTime();
		player.position.y += player.velocity.y * GetFrameTime();
	}

	void CheckMovementInput(Player& player)
	{		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			player.velocity.y = player.jumpForce;
		}

		//player.dest.y = player.position.y;
	}

	void PlayerScreenCollision(Player& player)
	{
		if (player.position.y <= 0)
		{
			player.position.y = 0;
		}

		if (player.position.y + player.texture.height >= GetScreenHeight())
		{
			player.position.y = static_cast<float>(GetScreenHeight()) - static_cast<float>(player.texture.height);
		}

		player.dest.y = player.position.y;
	}

	void DrawPlayer(Player player)
	{
		//DrawTexturePro(player.texture, player.source, player.dest, player.origin, player.rotation, RAYWHITE);
		DrawTexture(player.texture, static_cast<int>(player.position.x), static_cast<int>(player.position.y), RAYWHITE);
	}
}