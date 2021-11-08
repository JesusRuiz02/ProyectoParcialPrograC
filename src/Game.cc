#include "CommonHeaders.hh"
#include "Player.hh"
#include "Animation.hh"
#include "TileGroup.hh"
#include "Enemy.hh"


sf::CircleShape* circle{new sf::CircleShape()};

TextObject* textObj1{new TextObject(ASSETS_FONT_ARCADECLASSIC, 14, sf::Color::White, sf::Text::Bold)};

sf::Clock* gameClock{new sf::Clock()};
float deltaTime{};
Player* player1{};
GameObject* chest1{};
GameObject* light1{};
GameObject* Walls[6]{};
GameObject* Walls2[3]{};
GameObject* Walls3{};
GameObject* Walls4[4]{};
GameObject* Walls5[6]{};
GameObject* Walls6[6]{};
GameObject* Walls7[6]{};
GameObject* Walls8[4]{};
GameObject* Walls9[3]{};
GameObject* Walls10[3]{};
GameObject* Walls11[2]{};
GameObject* chest2{};
Enemy* enemy1{};
Animation* idleAnimation{new Animation()};
Animation* runAnimation{new Animation()};
float x = 50, y=30;
float x2=120, y2=170;
float x3=510, y3=300;


TileGroup* tileGroup{};
Tile* tile1{};

uint32 flags{};
    //flags += b2Draw::e_aabbBit;
    //flags += b2Draw::e_shapeBit;
    //flags += b2Draw::e_centerOfMassBit;
    //flags += b2Draw::e_pairBit;
    //flags += b2Draw::e_jointBit;

//Animation* lightIdle{};

Game::Game()
{
  window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
  event = new sf::Event();
  gravity = new b2Vec2(0.f, 20.f);
  world = new b2World(*gravity);
  drawPhysics = new DrawPhysics(window);
  gameObjects = new std::vector<GameObject*>();
  gameObjectsDeleteList = new std::vector<GameObject*>();

  player1 = new Player(ASSETS_SPRITES, 4.f, 16, 16, 0, 5, 500, 300, 200.f, b2BodyType::b2_dynamicBody, world, window);
  player1->SetTagName("Player");
  chest1 = new GameObject(ASSETS_SPRITES, 4.f, 16, 16, 6, 1, 300, 500, b2BodyType::b2_staticBody, world, window);
  chest1->SetTagName("chest");
  light1 = new GameObject(ASSETS_SPRITES, 4.f, 16, 16, 6, 3, 500, 500, b2BodyType::b2_staticBody, world, window);
  light1->SetTagName("light");
  enemy1 = new Enemy(ASSETS_SPRITES, 4.f, 16, 16, 0, 1, 400, 300, 200.f, b2BodyType::b2_dynamicBody, world, window);
  enemy1->SetTagName("Enemy");
  chest2= new GameObject(ASSETS_SPRITES, 4.f, 16, 16, 6, 1, 120, 130, b2BodyType::b2_staticBody, world, window);
  chest2->SetTagName("chest");
  for (int i2 = 0; i2 < 3; i2++)
  {
     Walls2[i2]= new GameObject(ASSETS_TILES, 4.f, 16, 1, 0, 0, x2, y2, b2BodyType::b2_staticBody, world, window);
     Walls2[i2]->SetTagName("wall");
     Walls9[i2]= new GameObject(ASSETS_TILES, 4.f, 16, 1, 0, 0, x3, 247 , b2BodyType::b2_staticBody, world, window);
     Walls10[i2]=new GameObject(ASSETS_TILES, 4.f, 16, 1, 0, 0, x3, 381 , b2BodyType::b2_staticBody, world, window);
     x2=x2+67;
     x3=x3+67;
  }
  x2=120;
  
  Walls3= new GameObject(ASSETS_TILES, 4.f, 1, 16, 0, 0, 80, 130, b2BodyType::b2_staticBody, world, window);
  Walls3->SetTagName("wall");
  Walls11[0]= new GameObject(ASSETS_TILES, 4.f, 1, 16, 0, 0, 80, 337, b2BodyType::b2_staticBody, world, window);
  Walls11[1]= new GameObject(ASSETS_TILES, 4.f, 1, 16, 0, 0, 80, 277, b2BodyType::b2_staticBody, world, window);
  Walls11[0]->SetTagName("wall");
  Walls11[1]->SetTagName("wall");
   for (int i = 0; i < 6; i++)
  {
    Walls[i] = new GameObject(ASSETS_TILES, 4.f, 32, 32, 0, 0, x, y, b2BodyType::b2_staticBody, world, window);
    Walls[i]->SetTagName("wall");
    x=x+135;
  }
  x=760;
  for (int i = 0; i < 4; i++)
  {
   Walls4[i]= new GameObject(ASSETS_TILES, 4.f, 16, 1, 0, 0, x2, 247 , b2BodyType::b2_staticBody, world, window);
   Walls4[i]->SetTagName("wall");
   Walls8[i]= new GameObject(ASSETS_TILES, 4.f, 16, 1, 0, 0, x2, 381 , b2BodyType::b2_staticBody, world, window);
   Walls8[i]->SetTagName("wall");
  
   x2=x2+67;

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
     y=y+130;
     y2=y2+130;
     x2=x2+130;
     
  }



  
 

  tileGroup = new TileGroup(window, 12, 12, ASSETS_MAPS, 4.f, 16, 16, ASSETS_TILES);

  contactEventManager = new ContactEventManager(gameObjects, gameObjectsDeleteList);


 // lightIdle = new Animation(light1->GetSprite(), 6, 11, 0.1f, 3);
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

  AddGameObject(player1);
  AddGameObject(chest1);
  AddGameObject(light1);
  AddGameObject(Walls11[0]);
  AddGameObject(Walls11[1]);
  for (int i = 0; i <6; i++)
  {
    AddGameObject(Walls[i]);
    AddGameObject(Walls5[i]);
    AddGameObject(Walls6[i]);
    AddGameObject(Walls7[i]);
  }
  for (int i2 = 0; i2 < 3; i2++)
  {
    AddGameObject(Walls2[i2]);
  }
  for (int i = 0; i < 4; i++)
  {
    AddGameObject(Walls4[i]);
  }
 
  
  
  AddGameObject(Walls3);
  
  AddGameObject(chest2);
  AddGameObject(enemy1);
  

  textObj1->SetTextStr("My game");
  idleAnimation = new Animation(player1->GetSprite(), 0, 5, 0.05f, 5);
  runAnimation = new Animation(player1->GetSprite(), 0, 5, 0.08f, 6);

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

  //circle->setPosition(player1->GetSprite()->getPosition());

 // lightIdle->Play(deltaTime);

  if(std::abs(InputSystem::Axis().x) > 0 || std::abs(InputSystem::Axis().y) > 0)
  {
    runAnimation->Play(deltaTime);
  }
  else
  {
    idleAnimation->Play(deltaTime);
  }
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
  //tile1->Draw();

  for(auto &gameObject : *gameObjects)
  {
    gameObject->Draw();
  }

  window->draw(*textObj1->GetText());
  world->DebugDraw();
}

//Keyboard, joysticks, etc.
void Game::Input()
{
  //player1->Move();
  enemy1->Move();
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