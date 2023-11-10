#pragma once

#include "header/raylib.h"

namespace FlappyBird
{
	struct Player 
	{
		Vector2 position = { 0, 0 };
		float speed = 0.0f;
		Vector2 velocity = { 0, 0 };
		//Vector2 acceleration = { 0, 0 };
		float gravity = 600.0;
		float jumpForce = -300.0f;

		Texture2D texture = Texture2D();
		Rectangle source = { 0, 0, 0, 0 };
		float scale = 0.0f;
		Rectangle dest = { 0, 0, 0, 0 };
		Vector2 origin = { 0, 0 };
		float rotation = 0;
	};

	Player InitPlayer();
	void UpdatePlayer(Player& player);
	void PlayerMovement(Player& player);
	void CheckMovementInput(Player& player);
	void PlayerScreenCollision(Player& player);
	void DrawPlayer(Player player);
}
