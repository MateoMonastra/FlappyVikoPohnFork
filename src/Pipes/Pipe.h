#pragma once
#include "header/raylib.h"

namespace FlappyBird
{
	struct Pipe
	{
		Vector2 position = { 0, 0 };
		float speed = 0.0f;
		float height = 0.0f;
		float width = 0.0f;
	};

	Pipe InitPipe();
	void UpdatePipe(Pipe& pipe);
	void DrawPipe(Pipe pipe);
}



