#pragma once
#include<SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Rigidbody.hh"
#include "GameObject.hh"

class Enemy : public GameObject
{
private:
  float EnemySpeed{};

  void FlipSprite();
public:
  Enemy(std::string textureUrl, float EnemyScale, int width, int height, int column, int row, float posX, float posY, float EnemySpeed, 
  b2BodyType bodyType, b2World*& world, sf::RenderWindow*& window);
  ~Enemy();
  sf::Sprite* GetSprite() const;
  void Move();

  void Update(float& deltaTime) override;
  void Draw() override;
};
