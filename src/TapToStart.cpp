#include "TapToStart.h"
#include "Constants.h"
#include "Scenes.h"

TapToStart::TapToStart () {
    logo = LoadTexture("assets/logov2.png");
    taptostart = LoadTexture("assets/taptostart.png");


}
void TapToStart::draw(){

    DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2 - 110, WHITE);

    DrawTexture(taptostart, screenWidth/2 - taptostart.width/2, screenHeight/2 - taptostart.height/2 + 330, WHITE);

}

void TapToStart::update() {

   if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ) {
         mouseX = GetMouseX();
         mouseY = GetMouseY();

        if ( mouseX >= screenWidth/2 - taptostart.width/2 &&
             mouseX <= screenWidth/2 + taptostart.width/2 &&
             mouseY >= screenHeight/2 - taptostart.height/2 + 330 &&
             mouseY <= screenHeight/2 + taptostart.height/2 + 330 ) {

                currentScene = Scenes::MainMenu;
        }
   }
}
