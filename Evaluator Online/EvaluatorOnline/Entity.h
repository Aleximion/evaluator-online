#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

using namespace std;

class Entity: public sf::Drawable, public sf::Transformable{
public:
    Entity();
    Entity(int x,int y,int width,int height);
    void setTexture(sf::Texture texture);
    sf::Texture getTexture();
    void Update();
    void setBoundsTexture(sf::Texture);
    void Deactivate();
    void Activate();
    bool IsActive();
    void ActivateText();
    void DeactivateText();
protected:
    sf::RectangleShape bounds;
    sf::Texture texture;
    int width,height;
    sf::Texture mouse_on,mouse_off;
    bool active,textActive;
    void (*onClick)();
    void (*onClick2)(int nr);
    int  onClick2_nr;
    bool apasat;
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const
    {
        target.draw(bounds,states);
    }
};

#endif // ENTITY_H
