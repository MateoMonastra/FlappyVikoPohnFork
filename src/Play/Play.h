#pragma once
#include "Game/Scenes.h"
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	void InitPlay();
	void RunPlay(bool isNewScene, Scenes previousScene, Scenes& scene, Music& music);
	void UnloadPlay();
}