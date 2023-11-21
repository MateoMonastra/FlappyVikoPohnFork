#pragma once
#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitMenu();
	void InitMenuButtons();
	void DrawMenu();
	void RunMenu(Scenes& scene, bool isNewScene);
}
