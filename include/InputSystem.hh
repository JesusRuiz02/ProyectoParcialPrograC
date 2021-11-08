#include<SFML/Graphics.hpp>

class InputSystem
{
private:
    
public:
    InputSystem(){}
    ~InputSystem(){}

    static sf::Vector2f Axis()
    {
    sf::Vector2f axis{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
      axis.x = 1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
      axis.x = -1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
      axis.y = -1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
      axis.y = 1;
    }

    return axis;
    }  
    static sf::Vector2f Arrows()
    {
    sf::Vector2f axis{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
      axis.x = 1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
      axis.x = -1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      axis.y = -1;
    }
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
      axis.y = 1;
    }

    return axis;
    }  
};


