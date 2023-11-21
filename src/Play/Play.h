#pragma once

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPlay();
	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene);
}