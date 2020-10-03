#include "BackgroundRenderer.h"
#include "raylib.h"
#include "Constants.h"

BackgroundRenderer::BackgroundRenderer () {
    /*
    background = LoadTexture("assets/background.png");
    */

    sh = LoadShader( "assets/powerup.vs", "assets/powerup.fs");
    hueAdjustLoc = GetShaderLocation(sh, "hueAdjust");
    hueAdjust = 0;
}

void BackgroundRenderer::draw() {
    SetShaderValue(sh, hueAdjustLoc, &hueAdjust, UNIFORM_FLOAT);
    BeginShaderMode(sh);

    DrawRectangle(0,0,screenWidth,screenWidth,WHITE);
    //DrawTexture(tttt,0,0,WHITE);

    EndShaderMode();
    hueAdjust += 0.01f;

    /*
    scrollingBack -= 2.0f;
    if (scrollingBack <= -background.width*2) scrollingBack = 0;

    DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
    */
}
