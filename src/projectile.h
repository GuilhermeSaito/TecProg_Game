#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player1.h"

class Projectile : public Menu
{
private:
  sf::Sprite sprite;
  sf::RectangleShape rect;

  //speed an positioning
  float linearSpeed;
  sf::Vector2f speed;
  sf::Vector2f pos;
  float angle;

  sf::Texture projectileTexture;

public:
  Projectile(sf::RenderWindow *window = NULL, sf::Vector2f playerPosition = {0, 0}, sf::Vector2f enemyPosition = {0, 0}, float ls = 5.f);
  ~Projectile();

  sf::FloatRect getBoundBox();

  void update(Entidade::Player::Player1 *p);
  void render();

  int Start() override { return 0; }
};
