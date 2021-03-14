#pragma once

#include "data.h"
#include "tile.h"

namespace Entidade
{
	class Entity
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

	public:
		Entity(sf::Vector2f pos = { 0 , 0 }, sf::Vector2f spee = { 0, 0 }, float hP = 100, float attack = 10);
		~Entity();

		const sf::Vector2f getPosition() const;
		void setPosition(const sf::Vector2f pos);
		const sf::Vector2f getSpeed() const;
		void setSpeed(const sf::Vector2f spee);
		const sf::Vector2f getSize() const;

		const float getHp() const;
		void setHp(const float hP);

		sf::FloatRect getBoundBox();
		void collisionInX(PhaseMap::Tiles::Tile* tile);
		void collisionInY(PhaseMap::Tiles::Tile* tile);
		void gravity();
		const bool getOnGround() const;
		void setOnGround(const bool onG);
		void jump();
		void setIsLookingRight(const bool r);

		const float getAttackDamage() const;
		void setAttackDamage(const float attack);
	};
}