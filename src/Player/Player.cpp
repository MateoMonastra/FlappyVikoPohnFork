#include "Player.h"

namespace FlappyBird
{
	Player InitPlayer()
	{
		Player player;

		player.speed = 700.0f;

		player.texture = LoadTexture("res/player.png");

		float xPos = static_cast<float>(GetScreenWidth() / 8);
		player.position = { xPos, static_cast<float>(GetScreenHeight() / 2) };

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
		CheckMovementInput(player);
	}

	void CheckMovementInput(Player& player)
	{		
		if (IsKeyDown(KEY_W))
		{
			player.position.y -= player.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_S))
		{
			player.position.y += player.speed * GetFrameTime();
		}

		player.dest.x = player.position.x;
		player.dest.y = player.position.y;
	}

	void DrawPlayer(Player player)
	{
		DrawTexturePro(player.texture, player.source, player.dest, player.origin, player.rotation, RAYWHITE);
	}
}