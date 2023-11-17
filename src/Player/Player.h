#pragma once

#include "Raylib/header/raylib.h"

#include "Game/Scenes.h"

namespace FlappyBird
{
	struct Player 
	{
		Vector2 topPosition = { 0, 0 };
		Vector2 velocity = { 0, 0 };
		const float PLAYER_GRAVITY = 600.0;
		const float JUMPFORCE = -300.0f;
		bool isJumping = false;

		Rectangle hitBox = {};

		Texture2D texture = Texture2D();
		Texture2D textureFly = Texture2D();
		Texture2D textureDrop = Texture2D();
		Rectangle source = { 0, 0, 0, 0 };

		float scale = 0.0f;
		Rectangle dest = { 0, 0, 0, 0 };
		Vector2 origin = { 0, 0 };

		float rotation = 0;

		int score = {0};
	};

	Player InitPlayer();
	void UpdatePlayer(Player& player, Scenes& scene);
	void PlayerMovement(Player& player);
	void CheckMovementInput(Player& player);
	void ChangeTexture(Player& player);
	void PlayerScreenCollision(Player& player, Scenes& scene);
	void DrawPlayer(Player player);
}
