#include "Pipes/Pipe.h"

namespace FlappyBird
{
	static int minHeight = 80;
	static int maxHeight = 400;
	static float screenOffset = 100.0f;
	static int verticalRandPos = GetRandomValue(0, 1);

	Pipe InitPipe()
	{
		Pipe pipe;

		pipe.speed = 300.0f;

		pipe.width = 90.0f;
		pipe.height = static_cast<float>(GetRandomValue(minHeight, maxHeight));

		pipe.position.x = static_cast<float>(GetScreenWidth() + screenOffset);

		if(verticalRandPos == 0)
			pipe.position.y = 0;
		else if(verticalRandPos == 1)
			pipe.position.y = static_cast<float>(GetScreenHeight() - pipe.height);

		return pipe;
	}

	void UpdatePipe(Pipe& pipe)
	{
		pipe.position.x -= pipe.speed * GetFrameTime();

		if (pipe.position.x + pipe.width < 0)
		{
			verticalRandPos = GetRandomValue(0, 1);

			pipe.height = static_cast<float>(GetRandomValue(minHeight, maxHeight));

			pipe.position.x = static_cast<float>(GetScreenWidth());

			if (verticalRandPos == 0)
				pipe.position.y = 0;
			else if (verticalRandPos == 1)
				pipe.position.y = static_cast<float>(GetScreenHeight() - pipe.height);

		}
	}

	void DrawPipe(Pipe pipe)
	{
		DrawRectangle(static_cast<int>(pipe.position.x), static_cast<int>(pipe.position.y), static_cast<int>(pipe.width), static_cast<int>(pipe.height), GREEN);
	}
}