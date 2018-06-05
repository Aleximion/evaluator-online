#ifndef BUTTON_H
#define BUTTON_H

#include "Entity.h"

class Button : public Entity
{
    public:
        Button();
        Button(string text,int x, int y, int width,int height);
        Button(int x, int y, int width,int height);
        Button(int x, int y, int width,int height,void (&func)());
        Button(int x,int y,int width,int height,void (&func)(int nr),int nr);
        string getText();
        int getWidth();
        int getHeight();
        void setText(string text);
        void setWidth(int width);
        void setHeight(int height);
        void doWhenClicked(void (&func)());
        void setTexture_mOn(sf::Texture texture);
        void setTexture_mOff(sf::Texture texture);
    private:
        string text;
        void putTexture();
};

#endif // BUTTON_H
