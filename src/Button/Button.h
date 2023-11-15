#pragma once
#include "Raylib/header/raylib.h"

namespace FlappyBird
{
	struct Button
	{
		Texture2D texture;
		Texture2D texturePressed;
		float x;
		float y;
		float width;
		float height;
		Color color;
		bool isSelected;
	};

	void InitButton(Button& button, Texture2D texture, Texture2D texturePressed, float x, float y, float width, float height, Color color);
	void DrawButton(Button& button);
	bool CheckCollisionButtonMouse(Vector2 mousePos, Button button);
	bool CheckMouseInput(Button button);
}
