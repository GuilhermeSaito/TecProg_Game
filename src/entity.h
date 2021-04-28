#pragma once

#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include "menu.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

namespace Entidade
{
	class Entity : public Menu
	{
	protected:
		sf::Vector2f position;
		sf::Vector2f speed;
		float walkSpeed;

		sf::RectangleShape healthBar;
		float hp;

		sf::RectangleShape rect;
		bool onGround;
		float jumpSpeed;
		float gravityAcceleration;

		sf::Sprite sprite;
		bool isLookingRight;

		float attackDamage;

		int points;

	public:
		Entity(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attack = 0, const int point = 0);
		virtual ~Entity();

		const sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f pos);
		const sf::Vector2f getSpeed() const;
		void setSpeed(const sf::Vector2f spee);
		const sf::Vector2f getSize() const;

		const float getHp() const;
		void setHp(const float hP);

		const sf::FloatRect getBoundBox() const;
		void collisionInX(PhaseMap::Tiles::Tile *tile);
		void collisionInY(PhaseMap::Tiles::Tile *tile);
		void gravity();
		const bool getOnGround() const;
		void setOnGround(const bool onG);
		void jump();
		void setIsLookingRight(const bool r);

		virtual const float getAttackDamage() const;
		void setAttackDamage(const float attack);

		const int getPoints() const;
		void setPoints(const int p);

		virtual json getSave() = 0;

		int Start() override { return 0; }
	};
}