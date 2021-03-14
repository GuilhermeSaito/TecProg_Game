#include "entity.h"

// using for know what collision is, erase this
#include <iostream>

using namespace Entidade;

Entity::Entity(sf::Vector2f pos, sf::Vector2f spee, float hP, float attack) :
	position(pos),
	speed(spee),
	hp(hP),
	walkSpeed(8),
	onGround(false),
	jumpSpeed(-20),
	gravityAcceleration((float)1.1),
	isLookingRight(true),
	attackDamage(attack)
{
	rect.setSize({ 48, 48 });	
}
Entity::~Entity()
{
}

const sf::Vector2f Entity::getPosition() const { return position; }
void Entity::setPosition(const sf::Vector2f pos) { position = pos; }
const sf::Vector2f Entity::getSpeed() const { return speed; }
const float Entity::getHp() const { return hp; }
void Entity::setHp(const float hP) { hp = hP; }
void Entity::setSpeed(const sf::Vector2f spee) { speed = spee; }
const sf::Vector2f Entity::getSize() const { return rect.getSize(); }

								// Rectangle located at  (x Position, Y Position) with a Size of (X rectSize, Y rectSize)
sf::FloatRect Entity::getBoundBox() { return sf::FloatRect(position.x, position.y, rect.getSize().x, rect.getSize().y); }
void Entity::collisionInX(PhaseMap::Tiles::Tile* tile)
{
	// Walking right
	if (speed.x > 0)
		position.x = tile->getBoundBox().left - rect.getSize().x;
	else if (speed.x < 0 && speed.y > gravityAcceleration)
		position.x = tile->getBoundBox().left - rect.getSize().x;
	else if (speed.x < 0)
		position.x = tile->getBoundBox().left + tile->getBoundBox().width;
	speed.x = 0;
}
void Entity::collisionInY(PhaseMap::Tiles::Tile* tile)
{
	// Falling
	if (speed.y > 0)
	{
		position.y = tile->getBoundBox().top - rect.getSize().y;
		onGround = true;
	}
	else if (speed.y < 0)
	{
		position.y = tile->getBoundBox().top + tile->getBoundBox().height;
		onGround = false;
	}
	speed.y = 0;
}
void Entity::gravity()
{
	if (!onGround)
	{
		speed.y += gravityAcceleration;
		position.y += speed.y;
	}
}
const bool Entity::getOnGround() const { return onGround; }
void Entity::setOnGround(const bool onG) { onGround = onG; }
void Entity::jump()
{
	if (onGround)
	{
		speed.y += jumpSpeed;
		onGround = false;
	}
}
void Entity::setIsLookingRight(const bool r) { isLookingRight = r; }

const float Entity::getAttackDamage() const { return attackDamage; }
void Entity::setAttackDamage(const float attack) { attackDamage = attack; }