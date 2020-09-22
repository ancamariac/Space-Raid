#ifndef SCENE_H
#define SCENE_H

#include "Drawable.h"
#include "Updateable.h"

#include <vector>

class Scene : public Drawable, public Updateable
{
private:
    std::vector<Drawable*> drawables;
    std::vector<Updateable*> updateables;

    public:
        Scene();
        virtual ~Scene();

        void addDrawable(Drawable* d);
        void addUpdateable(Updateable *u);

        void draw();
        void update();
};

#endif // SCENE_H
