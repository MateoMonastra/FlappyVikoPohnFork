#include "Pipes/Pipe.h"

namespace FlappyBird
{
	static int minHeight = 80;
	static int maxHeight = 400;
	static float screenOffset = 100.0f;

	Pipe InitPipe(float xPos)
	{
		Pipe pipe;

		pipe.texture = LoadTexture("res/PNG/Pipe.png");

		pipe.speed = 400.0f;

		pipe.width = 50.0f;

		pipe.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));

		pipe.topPosition.x = xPos;
		pipe.topPosition.y = 0.0f;

		pipe.botHeight = GetScreenHeight() - pipe.topHeight - pipe.separation;

		pipe.botPosition.x = pipe.topPosition.x;
		pipe.botPosition.y = static_cast<float>(GetScreenHeight() - pipe.botHeight);

		pipe.midPosition.x = pipe.topPosition.x + pipe.width / 2;
		pipe.midPosition.y = pipe.topPosition.y + pipe.topHeight;

		pipe.midHeight = pipe.botHeight;

		pipe.givePoints = true;

		pipe.topSource = {0,0,static_cast<float>(pipe.texture.width),static_cast<float>(pipe.texture.height)};
		pipe.topDest = { pipe.topPosition.x ,pipe.topPosition.y, pipe.width, pipe.topHeight };
		pipe.topOrigin = { 0, 0};

		pipe.botSource = { 0,0,static_cast<float>(pipe.texture.width),static_cast<float>(pipe.texture.height) };
		pipe.botDest = { pipe.botPosition.x ,pipe.botPosition.y, pipe.width, pipe.botHeight };
		pipe.botOrigin = { 0, 0};



		return pipe;
	}

	void UpdatePipe(Pipe& pipe)
	{
		pipe.topPosition.x -= pipe.speed * GetFrameTime();
		pipe.botPosition.x = pipe.topPosition.x;
		pipe.midPosition.x = pipe.topPosition.x + pipe.width / 2;

		if (pipe.topPosition.x + pipe.width < 0)
		{
			pipe.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));
			pipe.topPosition.x = static_cast<float>(GetScreenWidth()) + pipe.width;

			pipe.botHeight = GetScreenHeight() - pipe.topHeight - pipe.separation;
			pipe.botPosition.y = static_cast<float>(GetScreenHeight() - pipe.botHeight);

			pipe.midPosition.y = pipe.topPosition.y + pipe.topHeight;

			pipe.givePoints = true;

		}
		pipe.topDest = { pipe.topPosition.x ,pipe.topPosition.y, pipe.width, pipe.topHeight };
		pipe.botDest = { pipe.botPosition.x ,pipe.botPosition.y, pipe.width, pipe.botHeight };
	}

	void UpdatePipeReverse(Pipe& newPipe, Pipe& refPipe)
	{
		newPipe.topPosition.x -= newPipe.speed * GetFrameTime();
		newPipe.botPosition.x = newPipe.topPosition.x;
		newPipe.midPosition.x = newPipe.topPosition.x + newPipe.width / 2;

		if (newPipe.topPosition.x > GetScreenWidth())
		{
			newPipe.topHeight = refPipe.topHeight - newPipe.separation / 4;
			newPipe.topPosition.x = 0;

			newPipe.botHeight = refPipe.botHeight;
			newPipe.botPosition.y = refPipe.botPosition.y + newPipe.separation / 4;

			newPipe.midPosition.y = newPipe.topPosition.y + newPipe.topHeight;

			newPipe.givePoints = true;

		}
		newPipe.topDest = { newPipe.topPosition.x ,newPipe.topPosition.y, newPipe.width, newPipe.topHeight };
		newPipe.botDest = { newPipe.botPosition.x ,newPipe.botPosition.y, newPipe.width, newPipe.botHeight };

	}

	void StartReversePhasePipe(Pipe& firstPipe, Pipe& secondPipe,Pipe& thirdPipe)
	{
		firstPipe.separation = 160;
		
		secondPipe.separation = 160;

		thirdPipe.separation = 290;
		thirdPipe.speed = -500;

		firstPipe.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));
		firstPipe.topPosition.x = static_cast<float>(GetScreenWidth());

		firstPipe.botHeight = GetScreenHeight() - firstPipe.topHeight - firstPipe.separation;
		firstPipe.botPosition.y = static_cast<float>(GetScreenHeight() - firstPipe.botHeight);

		firstPipe.midPosition.y = firstPipe.topPosition.y + firstPipe.topHeight;

		firstPipe.givePoints = true;

		secondPipe.topHeight = static_cast<float>(GetRandomValue(minHeight, maxHeight));
		secondPipe.topPosition.x = static_cast<float>(GetScreenWidth() + GetScreenWidth() / 2);

		secondPipe.botHeight = GetScreenHeight() - secondPipe.topHeight - secondPipe.separation;
		secondPipe.botPosition.y = static_cast<float>(GetScreenHeight() - secondPipe.botHeight);

		secondPipe.midPosition.y = secondPipe.topPosition.y + secondPipe.topHeight;

		secondPipe.givePoints = true;

		thirdPipe.topHeight = firstPipe.topHeight;
		thirdPipe.topPosition.x = 0;

		thirdPipe.botHeight = firstPipe.botHeight;
		thirdPipe.botPosition.y = firstPipe.botPosition.y;

		thirdPipe.midPosition.y = thirdPipe.topPosition.y + thirdPipe.topHeight;

		thirdPipe.givePoints = true;
	}

	void DrawPipe(Pipe pipe)
	{
		DrawRectangle(static_cast<int>(pipe.topPosition.x), static_cast<int>(pipe.topPosition.y), static_cast<int>(pipe.width), static_cast<int>(pipe.topHeight), DARKPURPLE);
		
		DrawTexturePro(pipe.texture,pipe.topSource,pipe.topDest,pipe.topOrigin ,0, WHITE);
		

		DrawRectangle(static_cast<int>(pipe.botPosition.x), static_cast<int>(pipe.botPosition.y), static_cast<int>(pipe.width), static_cast<int>(pipe.botHeight), DARKPURPLE);
		
		DrawTexturePro(pipe.texture, pipe.botSource, pipe.botDest, pipe.botOrigin, 0, WHITE);
	}
}