#include "Helpers.h"
#include "raylib.h"

/* Check if a rectangle on-screen is clicked */
bool IsRecClicked ( int button, int x, int y, int w, int h ) {
    if ( IsMouseButtonPressed(button) ) {
        Vector2 mousePos = GetMousePosition();


        if ( mousePos.x >= x && mousePos.x <= x+w
            && mousePos.y >= y && mousePos.y <= y+h )
            return true;
    }

    return false;
}
