#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player1.h"

class Projectile
{
private:
  sf::Sprite sprite;
  sf::RectangleShape rect;

  //speed an positioning
  float linearSpeed;
  sf::Vector2f speed;
  sf::Vector2f pos;
  float angle;

public:
  Projectile(sf::Vector2f playerPosition, sf::Vector2f enemyPosition, float ls = 5.f);
  ~Projectile();

  sf::FloatRect getBoundBox();

  void update(Entidade::Player::Player1* p);
  void render(sf::RenderWindow &window);
};