#pragma once

#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitLoseScreen();
	void DrawLoseScreen();
	void InputLoseScreen(Scenes& scene);
	void RunLoseScreen(Scenes& scene, bool isNewScene);
}
