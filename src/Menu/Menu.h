#pragma once
#include "Game/Scenes.h"
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	void InitMenu();
	void InitMenuButtons();
	void DrawMenu();
	void RunMenu(Scenes& scene, bool isNewScene, Music& music);
}
