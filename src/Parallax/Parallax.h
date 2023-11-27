#pragma once
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	struct Parallax
	{
		Texture2D staticTexture = Texture2D();
		Texture2D backTexture = Texture2D();
		Texture2D middleTexture = Texture2D();
		Texture2D frontTexture = Texture2D();

		float backSpeed = 30.0f;
		float middleSpeed = 100.0f;
		float frontSpeed = 400.0f;

		float backXPos = 0.0f;
		float middleXPos = 0.0f;
		float frontXPos = 0.0f;

		float yPos = 0.0f;

		float rotation = 0.0f;
		float scale = 1.0f;
	};

	Parallax InitParallax();
	void UpdateParallax(Parallax& parallax);
	void DrawParallax(Parallax& parallax);
}
