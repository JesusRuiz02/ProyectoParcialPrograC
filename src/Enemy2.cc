#include "Enemy2.hh"



Enemy2::Enemy2(std::string textureUrl, float scale, int width, int height, int column, int row, float posX, float posY, float enemySpeed,
b2BodyType bodyType, b2World*& world, sf::RenderWindow*& window, float maxTime, sf::Vector2f direction) :
GameObject(textureUrl, scale, width, height, column, row, posX, posY, bodyType, world, window)
{
  this->enemySpeed = enemySpeed;
  this->maxTime = maxTime;
  this->direction = direction;

  animationSystem = new AnimationSystem{};

  animationSystem->AddAnimation("idleEnemy",new Animation(sprite, "assets/animations/enemy/idle.anim"));
  
  

  rigidbody->FreezeRotation(true);
}

Enemy2::~Enemy2()
{
}

sf::Sprite* Enemy2::GetSprite() const
{
  return sprite;
}


void Enemy2::Update(float& deltaTime)
{
  //animationEnemySystem->Update(deltaTime);
  GameObject::Update(deltaTime);
  currentTime += deltaTime;
  rigidbody->GetBody()->SetLinearVelocity(b2Vec2(-direction.x * enemySpeed,
  -direction.y * enemySpeed));
  if(currentTime>=1)
  {
    direction = sf::Vector2f(direction.x+0.01,  direction.y);
  }
   if(currentTime>=2)
  {
     direction = sf::Vector2f(direction.x*0, direction.y+0.01);
  }
   if(currentTime>=3)
  {
        direction = sf::Vector2f(-direction.x+0.01,direction.y*0);
  }
  if(currentTime>=4)
  {
        direction = sf::Vector2f(direction.x*0,-direction.y+0.01);
        currentTime=0;
        direction = sf::Vector2f(direction.x*0,direction.y*0);
  }

    
    

  
}

void Enemy2::Draw()
{
  GameObject::Draw();
}

void Enemy2::FlipSprite()
{
  sprite->setScale(direction.x > 0 ? scale : direction.x < 0 ? -scale :
  sprite->getScale().x,
  scale);
}
