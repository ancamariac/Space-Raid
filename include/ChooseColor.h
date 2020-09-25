#ifndef CHOOSECOLOR_H
#define CHOOSECOLOR_H

#include "ChooseColorButton.h"

class ChooseColor {
public:

    ChooseColorButton blueShipButton, redShipButton, greenShipButton, purpleShipButton;
    Texture2D nextButton, backButton;
    Vector2 nextPos, backPos;

    ChooseColor ();
    void draw ();
    void update();
    bool isNextButtonActive ();
};

#endif // CHOOSECOLOR_H
