#pragma once

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPlay();
	bool PlayerPipeCollision();
	void LoseCondition();
	void UpdatePlay();
	void DrawPlay();
	void RunPlay(bool isNewScene, Scenes previousScene);
}