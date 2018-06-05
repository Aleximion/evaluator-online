#ifndef MOUSEEVENTS_H
#define MOUSEEVENTS_H


class MouseEvents
{
    public:
        MouseEvents();
        virtual ~MouseEvents();
        static int mouse_x,mouse_y;
        static bool released;
        static bool pressed;
};

#endif // MOUSEEVENTS_H
