#pragma once
#include "Game/Scenes.h"

namespace FlappyBird
{
	void InitCredits();
	void DrawCredits();
	void CreditsInput(Scenes& scene);
	void UpdateCreditsMusic();
	void RunCredits(Scenes& scene, bool isNewScene);
}