#pragma once
#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitCredits();
	void DrawCredits();
	/*void UpdateCreditsMusic();*/
	void RunCredits(Scenes& scene, bool isNewScene);
}