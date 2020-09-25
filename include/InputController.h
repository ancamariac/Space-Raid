#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H


class InputController
{
    public:

        InputController();
        virtual ~InputController();
        void setLayout();
        void update ();
        void draw ();

    protected:

    private:

        int layout = 2;
};

#endif // INPUTCONTROLLER_H
