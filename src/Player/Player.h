#pragma once

#include "header/raylib.h"

namespace FlappyBird
{
	struct Player 
	{
		Vector2 position = { 0, 0 };
		Texture2D texture;
		Rectangle source = { 0, 0, 0, 0 };
		float scale = 0.0f;
		Rectangle dest = { 0, 0, 0, 0 };
		Vector2 origin = { 0, 0 };
	};

	Player InitPlayer();
	void UpdatePlayer();
	void CheckMovementInput();
	void DrawPlayer();
}
