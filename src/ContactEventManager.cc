#include "ContactEventManager.hh"
#include "GameObject.hh"
#include <TextObject.hh>
#include<iostream>
//TextObject* TextGameOver{ new TextObject(ASSETS_FONT_ARCADECLASSIC, 30, sf::Color::White, sf::Text::Bold)};

ContactEventManager::ContactEventManager(std::vector<GameObject*>*& gameObjects, std::vector<GameObject*>*& gameObjectsDeleteList )
{
  this->gameObjects = gameObjects;
  this->gameObjectsDeleteList = gameObjectsDeleteList;
 
  
}

ContactEventManager::~ContactEventManager()
{
}

void ContactEventManager::BeginContact(b2Contact* contact)
{
  GameObject* actorA{(GameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer};
  GameObject* actorB{(GameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer};

  if(actorA && actorB)
  {
   
    if(actorB->GetTagName().compare("chest") == 0)
    {
      gameObjectsDeleteList->push_back(actorB);
      score=score+1;
      std::cout<<"Score :"<< score<<std::endl;
      if (score>=3)
      {
       std::cout<<"Ganaste"<<std::endl;
      }
      
    }
    if (actorB->GetTagName().compare("enemy")== 0)
    {
      gameObjectsDeleteList->push_back(actorA);
      GameOver=true;
      std::cout<<"Game Over"<<std::endl;
    //  if (GameOver)
    //  {
    //   TextGameOver->SetTextStr("GameOver");
    //  }
      
     }
    
  }
}
void ContactEventManager::EndContact(b2Contact* contact)
{

}


