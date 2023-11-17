#pragma once

#include "Raylib/header/raylib.h"

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPlay();
	void CheckPauseInput(Scenes& scene);
	bool PlayerPipeCollision(Vector2 pipePosition, float pipeHeight);
	void LoseCondition(Scenes& scene);
	void UpdatePlay(Scenes& scene);
	void DrawPlayerScore();
	void DrawPlay();
	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene);
}