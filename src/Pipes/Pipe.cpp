#include "Pipes/Pipe.h"
#include <iostream>

namespace FlappyBird
{
	static int minHeight = 80;
	static int maxHeight = 400;
	static float screenOffset = 100.0f;

	Pipe InitPipe(float xPos)
	{
		Pipe pipe;

		pipe.texture = LoadTexture("res/PNG/Pipe.png");

		pipe.speed = 450.0f;

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
		newPipe.topPosition.x += newPipe.speed * GetFrameTime();
		newPipe.botPosition.x = newPipe.topPosition.x;
		newPipe.midPosition.x = newPipe.topPosition.x + newPipe.width / 2;

		if (newPipe.topPosition.x > GetScreenWidth())
		{
			newPipe.topHeight = refPipe.topHeight - newPipe.separation / 4;
			newPipe.topPosition.x = 0;

			newPipe.botHeight = refPipe.botHeight;
			newPipe.botPosition.y = refPipe.botPosition.y + newPipe.separation / 3;

			newPipe.midPosition.y = newPipe.topPosition.y + newPipe.topHeight;

			newPipe.givePoints = true;

		}
		newPipe.topDest = { newPipe.topPosition.x ,newPipe.topPosition.y, newPipe.width, newPipe.topHeight };
		newPipe.botDest = { newPipe.botPosition.x ,newPipe.botPosition.y, newPipe.width, newPipe.botHeight };
	}

	void UpdatepPipeSpeed(Pipe& firstPipe, Pipe& secondPipe, Pipe& thirdPipe)
	{
		int speedUpdate = 50;

		firstPipe.speed += speedUpdate;

		secondPipe.speed += speedUpdate;
		
		thirdPipe.speed += speedUpdate;
	}

	void StartReversePhasePipe(Pipe& firstPipe, Pipe& secondPipe,Pipe& thirdPipe)
	{
		firstPipe.separation = 180;
		
		secondPipe.separation = 180;

		thirdPipe.separation = 330;
		thirdPipe.speed = 300;

		thirdPipe.topHeight = secondPipe.topHeight - thirdPipe.separation / 4;
		thirdPipe.topPosition.x = 0;

		thirdPipe.botHeight = secondPipe.botHeight;
		thirdPipe.botPosition.y = secondPipe.botPosition.y + secondPipe.separation / 3;

		thirdPipe.midPosition.y = secondPipe.topPosition.y + secondPipe.topHeight;

		thirdPipe.givePoints = true;
	}

	void DrawPipe(Pipe pipe)
	{
		//DrawRectangle(static_cast<int>(pipe.topPosition.x), static_cast<int>(pipe.topPosition.y), static_cast<int>(pipe.width), static_cast<int>(pipe.topHeight), DARKPURPLE);
		
		DrawTexturePro(pipe.texture,pipe.topSource,pipe.topDest,pipe.topOrigin ,0, WHITE);
		

		//DrawRectangle(static_cast<int>(pipe.botPosition.x), static_cast<int>(pipe.botPosition.y), static_cast<int>(pipe.width), static_cast<int>(pipe.botHeight), DARKPURPLE);
		
		DrawTexturePro(pipe.texture, pipe.botSource, pipe.botDest, pipe.botOrigin, 0, WHITE);
	}
}