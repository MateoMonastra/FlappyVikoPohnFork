#include "Rules.h"

#include "Raylib/header/raylib.h"

#include "Button/Button.h"

namespace FlappyBird
{
	static Texture2D rulesTexture;

	static Button backMenuRulesButton;
	static Texture2D backMenuRulesButtonTexture;
	static Texture2D backMenuRulesButtonPressedTexture;

	static void UnloadRules()
	{
		UnloadTexture(rulesTexture);
		UnloadTexture(backMenuRulesButtonTexture);
		UnloadTexture(backMenuRulesButtonPressedTexture);
	
	}

	static void RulesInput(Scenes& scene)
	{
		if (CheckCollisionButtonMouse(GetMousePosition(), backMenuRulesButton))
		{
			backMenuRulesButton.isSelected = true;

			if (CheckMouseInput(backMenuRulesButton))
			{
				UnloadRules();
				scene = Scenes::Menu;
			}
		}
		else
			backMenuRulesButton.isSelected = false;
	}

	void InitRules()
	{
		rulesTexture = LoadTexture("res/PNG/rules.png");
		backMenuRulesButtonTexture = LoadTexture("res/PNG/backmenubutton.png");
		backMenuRulesButtonPressedTexture = LoadTexture("res/PNG/backmenubuttonpressed.png");

		const float buttonWidth = static_cast<float>(backMenuRulesButtonTexture.width);
		const float buttonHeight = static_cast<float>(backMenuRulesButtonTexture.height);
		float buttonXPos = static_cast<float>(GetScreenWidth()) - buttonWidth - 10;
		float buttonYPos = static_cast<float>(GetScreenHeight()) - buttonHeight - 10;

		InitButton(backMenuRulesButton, backMenuRulesButtonTexture, backMenuRulesButtonPressedTexture, buttonXPos, buttonYPos, buttonWidth, buttonHeight, RAYWHITE);
	}

	void DrawRules()
	{
		BeginDrawing();

		DrawTexture(rulesTexture, 0, 0, RAYWHITE);
		DrawButton(backMenuRulesButton);

		EndDrawing();
	}

	void RunRules(Scenes& scene, bool isNewScene)
	{
		if (isNewScene)
		{
			InitRules();
		}

		DrawRules();
		RulesInput(scene);
	}
}