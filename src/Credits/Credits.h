#pragma once
#include "Game/Scenes.h"
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	void InitCredits();
	void DrawCredits();
	void RunCredits(Scenes& scene, bool isNewScene, Music& music);
}