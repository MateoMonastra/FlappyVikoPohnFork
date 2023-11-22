#pragma once
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	struct Pipe
	{
		Vector2 topPosition = { 0, 0 };
		Vector2 midPosition = { 0, 0 };
		Vector2 botPosition = { 0, 0 };

		float separation = 160.0f;

		float speed = 0.0f;
		
		float topHeight = 0.0f;
		float midHeight = 0.0f;
		float botHeight = 0.0f;

		float width = 0.0f;

		bool givePoints = false;
	};

	Pipe InitPipe(float xPos);
	void UpdatePipe(Pipe& pipe);
	void DrawPipe(Pipe pipe);
}



