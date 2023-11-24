#include "Parallax/Parallax.h"

namespace FlappyBird
{
    Parallax InitParallax()
    {
        Parallax parallax;

        parallax.backTexture = LoadTexture("res/PNG/parback.png");
        parallax.middleTexture = LoadTexture("res/PNG/parmid.png");
        parallax.frontTexture = LoadTexture("res/PNG/parfront.png");

        return parallax;
    }

    void UpdateParallax(Parallax& parallax)
    {
        parallax.backXPos -= parallax.backSpeed * GetFrameTime();
        parallax.middleXPos -= parallax.middleSpeed * GetFrameTime();
        parallax.frontXPos -= parallax.frontSpeed * GetFrameTime();

        if (parallax.backXPos <= -parallax.backTexture.width)
        {
            parallax.backXPos = 0;
        }

        if (parallax.middleXPos <= -parallax.middleTexture.width)
        {
            parallax.middleXPos = 0;
        }

        if (parallax.frontXPos <= -parallax.frontTexture.width)
        {
            parallax.frontXPos = 0;
        }
    }

    void DrawParallax(Parallax& parallax)
    {
        Vector2 firstBack = { parallax.backXPos , 0 };
        Vector2 secondBack = { parallax.backTexture.width + parallax.backXPos, 0 };

        Vector2 firstMiddle = { parallax.middleXPos, 0 };
        Vector2 secondMiddle = { parallax.middleTexture.width + parallax.middleXPos, 0 };

        Vector2 firstFront = { parallax.frontXPos, 0 };
        Vector2 secondFront = { parallax.frontTexture.width + parallax.frontXPos, 0 };

        DrawTextureEx(parallax.backTexture, firstBack, parallax.rotation, parallax.scale, WHITE);
        DrawTextureEx(parallax.backTexture, secondBack, parallax.rotation, parallax.scale, WHITE);

        DrawTextureEx(parallax.middleTexture, firstMiddle, parallax.rotation, parallax.scale, WHITE);
        DrawTextureEx(parallax.middleTexture, secondMiddle, parallax.rotation, parallax.scale, WHITE);

        DrawTextureEx(parallax.frontTexture, firstFront, parallax.rotation, parallax.scale, WHITE);
        DrawTextureEx(parallax.frontTexture, secondFront, parallax.rotation, parallax.scale, WHITE);
    }
}