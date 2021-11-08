#include "Enemy.hh"
#include "InputSystem.hh"

Enemy::Enemy(std::string textureUrl, float EnemyScale, int width, int height, int column, int row,
float posX, float posY, float playerSpeed, b2BodyType bodyType, b2World*& world, sf::RenderWindow*& window) :
GameObject(textureUrl, EnemyScale, width, height, column, row, posX, posY, bodyType, world, window)
{
  this->EnemySpeed = EnemySpeed;
  rigidbody->FreezeRotation(true);
}

Enemy::~Enemy()
{
}

sf::Sprite* Enemy::GetSprite() const
{
  return sprite;
}

void Enemy::Update(float& deltaTime)
{
  GameObject::Update(deltaTime);
  Move();
 
}

void Enemy::Draw()
{
  GameObject::Draw();

}

void Enemy::Move()
{
  rigidbody->GetBody()->SetLinearVelocity(b2Vec2(InputSystem::Arrows().x * EnemySpeed,
  InputSystem::Arrows().y * EnemySpeed));
  FlipSprite();
}
void Enemy::FlipSprite()
{
  sprite->setScale(InputSystem::Arrows().x > 0 ? scale : InputSystem::Arrows().x < 0 ? -scale :
  sprite->getScale().x,
  scale);
}