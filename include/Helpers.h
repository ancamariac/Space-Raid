#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "raylib.h"

bool IsRecClicked ( int button, int x, int y, int w, int h );

bool IsPointInTriangle (Vector2 pt, Vector2 v1, Vector2 v2, Vector2 v3);


#endif // HELPERS_H_INCLUDED
