#include "Player2.h"

using namespace Entidade::Player;

Player2::Player2(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : Entity(window, pos, spee, hP, attackDamage, point),
																																 contAnimation(0)
{
	if (!player2Image.loadFromFile("src/data/players/player2Image.png"))
		EXIT_FAILURE;

	rect.setPosition(pos);

	sprite.setTexture(player2Image);
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Green);
}
Player2::~Player2()
{
	window = NULL;
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

void Player2::draw()
{
	window->draw(healthBar);

	window->draw(sprite);
}

json Player2::getSave()
{
	json j;
	if ((position.x != 2 * 48) && (position.y != 27 * 48))
	{
		j["players2"]["player2PositionX"] = position.x;
		j["players2"]["player2PositionY"] = position.y;
		j["players2"]["hp"] = hp;
	}

	return j;
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