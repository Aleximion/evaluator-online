#include "Button.h"
#include<iostream>
#include "MouseEvents.h"
Button::Button()
{
    this->text="\0";
    this->width=this->height=0;
    this->onClick=NULL;
    this->onClick2=NULL;
        this->onClick2_nr=0;
    this->bounds.setPosition(0,0);
    this->bounds.setSize(sf::Vector2f(0,0));
}
Button::Button(string text,int x, int y,int width,int height)
{
    this->text=text;
    this->width=width;
    this->height=height;
    this->onClick=NULL;
        this->onClick2_nr=0;
    this->onClick2=NULL;
    this->bounds.setPosition(x,y);
    this->bounds.setSize(sf::Vector2f(width,height));
    this->setPosition(x,y);
}
Button::Button(int x, int y,int width,int height)
{
    this->text="Insert text here";
    this->width=width;
    this->height=height;
    this->onClick=NULL;
    this->onClick2=NULL;
        this->onClick2_nr=0;
    this->bounds.setPosition(x,y);
    this->bounds.setSize(sf::Vector2f(width,height));
    this->setPosition(x,y);
}
Button::Button(int x, int y,int width,int height,void (&func)())
{
    this->text="Insert text here";
    this->width=width;
    this->height=height;
    this->onClick=&func;
    this->onClick2=NULL;
    this->onClick2_nr=0;
    this->bounds.setPosition(x,y);
    this->bounds.setSize(sf::Vector2f(width,height));
    this->setPosition(x,y);
}
Button::Button(int x, int y,int width,int height,void (&func)(int nr),int nr)
{
    this->text="Insert text here";
    this->width=width;
    this->height=height;
    this->onClick=NULL;
    this->onClick2=&func;
    this->onClick2_nr=nr;
    this->bounds.setPosition(x,y);
    this->bounds.setSize(sf::Vector2f(width,height));
    this->setPosition(x,y);
}
void Button::doWhenClicked(void (&func)())
{
    this->onClick=&func;
}
void Button::setTexture_mOff(sf::Texture texture)
{
    this->mouse_off=texture;
}
void Button::setTexture_mOn(sf::Texture texture)
{
    this->mouse_on=texture;
}
int Button::getHeight()
{
    return height;
}
int Button::getWidth()
{
    return width;
}
void Button::setWidth(int width)
{
    this->width=width;
    bounds.setSize(sf::Vector2f(this->width,this->height));
}
void Button::setHeight(int height)
{
    this->height=height;
    bounds.setSize(sf::Vector2f(this->width,this->height));
}
void Entity::Update()
{
    if(active)
    {
        sf::Vector2f poz=this->getPosition();
        if(MouseEvents::mouse_x>=poz.x&&MouseEvents::mouse_x<=poz.x+width&&MouseEvents::mouse_y>=poz.y&&MouseEvents::mouse_y<=poz.y+height)
        {
            bounds.setTexture(&mouse_on);
            if(MouseEvents::pressed&&sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!apasat)
            {
                cout<<"DA"<<endl;
                if(onClick!=NULL){
                (*onClick)();
                }
                if(onClick2!=NULL){
                    (*onClick2)(onClick2_nr);
                }
                apasat=true;
            }
            else if(MouseEvents::released) apasat=false;
        }
        else
        {
            bounds.setTexture(&mouse_off);
        }
    }
    else
    bounds.setTexture(&mouse_off);
}
