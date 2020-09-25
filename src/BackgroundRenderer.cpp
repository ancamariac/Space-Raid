#include "BackgroundRenderer.h"
#include "raylib.h"

BackgroundRenderer::BackgroundRenderer () {
    background = LoadTexture("assets/background.png");
}

void BackgroundRenderer::draw(){

    scrollingBack -= 2.0f;
    if (scrollingBack <= -background.width*2) scrollingBack = 0;

    DrawTextureEx(background, (Vector2){ scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 0 }, 0.0f, 2.0f, WHITE);
}
