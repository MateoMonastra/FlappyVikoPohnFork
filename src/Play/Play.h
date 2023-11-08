#pragma once

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPlay();
	void UpdatePlay();
	void DrawPlay();
	void RunPlay(bool isNewScene, Scenes previousScene);
}