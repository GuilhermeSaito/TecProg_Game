#include "player1.h"

using namespace Entidade::Player;

Player1::Player1(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) :
	Entity(pos, spee, hP, attackDamage),
	contAnimation(0)
{
	rect.setPosition(pos);

	sprite.setTexture(*(Data::getInstance()->getPlayer1Texture()));
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Blue);
}
Player1::~Player1()
{
}

void Player1::movementation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (position.x >= 48))
	{
		speed.x = -walkSpeed;
		position.x += speed.x;
		isLookingRight = false;
		updateContAnimation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		speed.x = walkSpeed;
		position.x += speed.x;
		isLookingRight = true;
		updateContAnimation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		jump();

	rect.setPosition(position);
	sprite.setPosition(position);

	healthBar.setSize(sf::Vector2f(hp, 20));
	healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));

	spriteAnimation();
}

void Player1::draw(sf::RenderWindow& window)
{
	window.draw(healthBar);

	window.draw(sprite);
}

void Player1::spriteAnimation()
{
	if (isLookingRight)
		sprite.setTextureRect(sf::IntRect(47 * contAnimation, 48, 47, 48));
	else
		sprite.setTextureRect(sf::IntRect(47 * contAnimation, 0, 47, 48));
}

void Player1::updateContAnimation()
{
	sf::Time elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 0.3)
	{
		contAnimation++;
		clock.restart();
	}
	if (contAnimation > 2)
		contAnimation = 0;
}