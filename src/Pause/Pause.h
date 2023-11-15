#pragma once
#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitPause();
	void DrawPause();
	void InputPause(Scenes& scene);
	void RunPause(Scenes& scene, bool isNewScene);
}
