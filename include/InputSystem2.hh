#include<SFML/Graphics.hpp>

class InputSystem2
{
private:
    
public:
    InputSystem2(){}
    ~InputSystem2(){}

    static sf::Vector2f Axis()
    {
    sf::Vector2f axis{};

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)  )
    {
      axis.x = 1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  )
    {
      axis.x = -1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  )
    {
      axis.y = -1;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) )
    {
      axis.y = 1;
    }

    return axis;
    }  
};