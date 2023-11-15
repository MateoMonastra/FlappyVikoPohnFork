#pragma once

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPlay();
	void CheckPauseInput(Scenes& scene);
	bool PlayerPipeCollision();
	void LoseCondition(Scenes& scene);
	void UpdatePlay(Scenes& scene);
	void DrawGameVersion();
	void DrawPlay();
	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene);
}