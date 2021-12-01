#include "Player.hh"
#include "TileGroup.hh"
#include "Enemy.hh"
#include "Enemy2.hh"
#include "ContactEventManager.hh"
#include "CommonHeaders.hh"

sf::CircleShape* circle{new sf::CircleShape()};

TextObject* textObj1{new TextObject(ASSETS_FONT_ARCADECLASSIC, 14, sf::Color::White, sf::Text::Bold)};


sf::Clock* gameClock{new sf::Clock()};
float deltaTime{};
Player* player1{};
GameObject* chest1{};
GameObject* light1{};
GameObject* Walls[6]{};
GameObject* Walls2[5]{};
GameObject* Walls3{};
GameObject* Walls4[6]{};
GameObject* Walls5[6]{};
GameObject* Walls6[6]{};
GameObject* Walls7[6]{};
GameObject* Walls8[6]{};
GameObject* Walls9[5]{};
GameObject* Walls10[5]{};
GameObject* Walls11[2]{};
GameObject* Walls12[6]{};
GameObject* Walls13[5]{};
GameObject* chest2{};
GameObject* light2{};
Enemy* MiniEnemy{};
GameObject* Sword{};
GameObject* Decoration{};
GameObject* chest3{};
Enemy* enemy2{};
Enemy* enemy1{};
Enemy* enemy3{};
Enemy* enemy4{};
Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};
float x = 50, y=30;
float x2=110, y2=190;
float x3=510, y3=300;


TileGroup* tileGroup{};
Tile* tile1{};

uint32 flags{};
    //flags += b2Draw::e_aabbBit;
    //flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_centerOfMassBit;
    //flags += b2Draw::e_pairBit;
    //flags += b2Draw::e_jointBit;

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();
  gravity = new b2Vec2(0.f, 0.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  gameObjects = new std::vector<GameObject*>();
  gameObjectsDeleteList = new std::vector<GameObject*>();
  MiniEnemy = new Enemy(ASSETS_SPRITES, 3.f, 16, 16, 0, 5, 400, 350,100.f, b2BodyType::b2_dynamicBody, world, window, 2.f,sf::Vector2f(1,1));
  MiniEnemy->SetTagName("enemy");
  player1 = new Player(ASSETS_SPRITES, 3.f, 16, 16, 0, 5, 90, 110, 200.f, b2BodyType::b2_dynamicBody, world, window);
  player1->SetTagName("Player");
  chest1 = new GameObject(ASSETS_SPRITES, 3.f, 16, 16, 6, 1, 400, 600, b2BodyType::b2_staticBody, world, window);
  chest1->SetTagName("chest");
  light1 = new GameObject(ASSETS_SPRITES, 3.f, 16, 16, 6, 3, 110, 130, b2BodyType::b2_staticBody, world, window);
  light1->SetTagName("light");
  light2 = new GameObject(ASSETS_SPRITES, 3.f, 16, 16, 6, 3, 110, 250, b2BodyType::b2_staticBody, world, window);
  light2->SetTagName("light");
  enemy1 = new Enemy(ASSETS_SPRITES, 3.f, 16, 16, 0, 1, 500, 200, 200.f, b2BodyType::b2_dynamicBody, world, window,2.f,sf::Vector2f(0,-1));
  enemy1->SetTagName("enemy");
  enemy4 = new Enemy(ASSETS_SPRITES, 3.f, 16, 16, 0, 1, 600, 380, 200.f, b2BodyType::b2_dynamicBody, world, window,1.f,sf::Vector2f(-1,0));
  enemy4->SetTagName("enemy");
  enemy3 = new Enemy(ASSETS_SPRITES, 3.f, 16, 16, 0, 1, 90, 380, 200.f, b2BodyType::b2_dynamicBody, world, window,1.f,sf::Vector2f(1,0));
  enemy3->SetTagName("enemy");
  enemy2 = new Enemy(ASSETS_SPRITES, 3.f, 16, 16, 0, 1, 380, 500, 200.f, b2BodyType::b2_dynamicBody, world, window,3.f,sf::Vector2f(-1,0));
  enemy2->SetTagName("enemy");
  chest2= new GameObject(ASSETS_SPRITES, 3.f, 16, 16, 6, 1, 162, 130, b2BodyType::b2_staticBody, world, window);
  chest2->SetTagName("chest");
  Sword = new GameObject(ASSETS_TILES, 4, 16, 16, 1, 3, 700, 130,b2BodyType::b2_staticBody,world, window);
  Sword->SetTagName("Decoration");
  chest3= new GameObject(ASSETS_SPRITES, 3.f, 16, 16, 6, 1, 700, 300, b2BodyType::b2_staticBody, world, window);
  chest3->SetTagName("chest");

  Decoration = new GameObject(ASSETS_TILES, 3.f, 16, 16, 2, 4, 20, 640, b2BodyType::b2_staticBody, world, window);
  Decoration->SetTagName("Decoration");

  for (int i2 = 0; i2 < 5; i2++)
  {
     Walls2[i2]= new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x2, y2, b2BodyType::b2_staticBody, world, window);
     Walls2[i2]->SetTagName("wall");
     Walls9[i2]= new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x3, 297 , b2BodyType::b2_staticBody, world, window);
     Walls10[i2]=new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x3, 431 , b2BodyType::b2_staticBody, world, window);
     Walls13[i2]=new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x3, 565 , b2BodyType::b2_staticBody, world, window);
     Walls10[i2]->SetTagName("wall");
     Walls9[i2]->SetTagName("wall");
     
     x2=x2+32;
     x3=x3+32;
  }
  x2=110;
   for (int i = 0; i < 6; i++)
  {
    Walls[i] = new GameObject(ASSETS_TILES, 4.f, 32, 32, 0, 0, x, y, b2BodyType::b2_staticBody, world, window);
    Walls[i]->SetTagName("wall");
    x=x+135;
  }
  x=760;
  for (int i = 0; i < 6; i++)
  {
   Walls4[i]= new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x2, 297 , b2BodyType::b2_staticBody, world, window);
   Walls4[i]->SetTagName("wall");
   Walls8[i]= new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x2, 431 , b2BodyType::b2_staticBody, world, window);
   Walls8[i]->SetTagName("wall");
   Walls12[i]=new GameObject(ASSETS_TILES, 1.f, 32, 32, 0, 0, x2, 565, b2BodyType::b2_staticBody, world, window);
   Walls12[i]->SetTagName("wall");
  
   x2=x2+32;

  }
  y2=160;
  y=160;
  x2=50;
  for (int i = 0; i < 6; i++)
  {
     Walls5[i]=new GameObject(ASSETS_TILES, 4.f, 1, 32, 0, 0, x, y, b2BodyType::b2_staticBody, world, window);
     Walls5[i]->SetTagName("wall");
     Walls6[i]= new GameObject(ASSETS_TILES, 4.f, 1, 32, 0, 0, 0, y2, b2BodyType::b2_staticBody, world, window);
     Walls6[i]->SetTagName("wall");
     Walls7[i]= new GameObject(ASSETS_TILES, 4.f, 32, 32, 0, 0, x2, 700, b2BodyType::b2_staticBody, world, window);
     Walls7[i]->SetTagName("wall");
     y=y+130;
     y2=y2+130;
     x2=x2+130;
     
  }



  
 

  tileGroup = new TileGroup(window, 12, 12, ASSETS_MAPS, 4.f, 16, 16, ASSETS_TILES);

  contactEventManager = new ContactEventManager(gameObjects, gameObjectsDeleteList);



 
 
}

Game::~Game()
{
}

//Starting things
void Game::Start()
{
  flags += b2Draw::e_shapeBit;
  world->SetDebugDraw(drawPhysics);
  drawPhysics->SetFlags(flags);
  world->SetContactListener(contactEventManager);
  AddGameObject(enemy3);
  AddGameObject(enemy4);
  AddGameObject(player1);
  AddGameObject(chest1);
  AddGameObject(light1);
  AddGameObject(light2);
  AddGameObject(Sword);
  AddGameObject(Decoration);
  AddGameObject(chest3);
  AddGameObject(enemy2);
  for (int i = 0; i <6; i++)
  {
    AddGameObject(Walls[i]);
    AddGameObject(Walls5[i]);
    AddGameObject(Walls6[i]);
    AddGameObject(Walls7[i]);
    AddGameObject(Walls4[i]);
    AddGameObject(Walls8[i]);
    AddGameObject(Walls12[i]);
  }
  
 
 
  for (int i = 0; i < 5; i++)
  {
    AddGameObject(Walls9[i]);
    AddGameObject(Walls2[i]);
    AddGameObject(Walls10[i]);
    AddGameObject(Walls13[i]);
  }
  
  
 
  
  AddGameObject(chest2);
  AddGameObject(enemy1);
  AddGameObject(MiniEnemy);

  textObj1->SetTextStr("My game");

  

  /*circle->setRadius(2.f);
  circle->setFillColor(sf::Color::Green);
  circle->setOutlineColor(sf::Color::Green);*/
}

void Game::Initialize()
{
  Start();
  MainLoop();
}

void Game::UpdatePhysics()
{
  world->ClearForces();
  world->Step(deltaTime, 8, 8);
}

//Logic, animations, etc
void Game::Update()
{
  deltaTime = gameClock->getElapsedTime().asSeconds();
  gameClock->restart();

  for(auto &gameObject : *gameObjects)
  {
    gameObject->Update(deltaTime);
  }
  //  if (==true)
  //{
  // window->draw(*TextGameOver->GetText());
 // }

  //circle->setPosition(player1->GetSprite()->getPosition());

  //lightIdle->Play(deltaTime);

  /*if(std::abs(InputSystem::Axis().x) > 0 || std::abs(InputSystem::Axis().y) > 0)
  {
    runAnimation->Play(deltaTime);
  }
  else
  {
    idleAnimation->Play(deltaTime);
  }*/
}

void Game::MainLoop()
{
  while (window->isOpen())
  {
    while(window->pollEvent(*event))
    {
      if(event->type == sf::Event::Closed)
      {
        window->close();
      }
    }

    UpdatePhysics();
    Input();
    Update();
    Render();
  }
  Destroy();
}

void Game::Render()
{
  for(auto& gameobject: *gameObjectsDeleteList)
  {
      gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), gameobject), gameObjects->end());
      delete gameobject;
  }
  gameObjectsDeleteList->clear();

  window->clear(sf::Color::Black);
  Draw();
  window->display();
}

//Drawing sprites or geometry.
void Game::Draw()
{
  //player1->Draw();
  //window->draw(*circle);

  tileGroup->Draw();

  for(auto &gameObject : *gameObjects)
  {
    gameObject->Draw();
  }
  
  

  window->draw(*textObj1->GetText());
  //world->DebugDraw();
}

//Keyboard, joysticks, etc.
void Game::Input()
{
}

void Game::Destroy()
{
  delete window;
  delete event;
}

void Game::AddGameObject(GameObject* gameObject)
{
  gameObjects->push_back(gameObject);
}