#pragma once
#include "Button/Button.h"
#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitMenu();
	void InitMenuButtons();
	void DrawMenu();
	void MenuInput(Scenes& scene);
	void RunMenu(Scenes& scene, bool isNewScene);
}
