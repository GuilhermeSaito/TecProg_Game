#include "Player2.h"

using namespace Entidade::Player;

Player2::Player2(sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage) : Entity(pos, spee, hP, attackDamage),
																					  contAnimation(0)
{
	rect.setPosition(pos);

	sprite.setTexture(*(Data::getInstance()->getPlayer2Texture()));
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Green);
}
Player2::~Player2()
{
}

void Player2::movementation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (position.x >= 48))
	{
		speed.x = -walkSpeed;
		position.x += speed.x;
		isLookingRight = false;
		updateContAnimation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		speed.x = walkSpeed;
		position.x += speed.x;
		isLookingRight = true;
		updateContAnimation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		jump();

	rect.setPosition(position);
	sprite.setPosition(position);

	healthBar.setSize(sf::Vector2f(hp, 20));
	healthBar.setPosition(sf::Vector2f(position.x - 10, position.y - 25));

	spriteAnimation();
}

void Player2::draw(sf::RenderWindow &window)
{
	window.draw(healthBar);

	window.draw(sprite);
}

void Player2::spriteAnimation()
{
	if (isLookingRight)
		sprite.setTextureRect(sf::IntRect(47 * contAnimation, 48, 47, 48));
	else
		sprite.setTextureRect(sf::IntRect(47 * contAnimation, 0, 47, 48));
}

void Player2::updateContAnimation()
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