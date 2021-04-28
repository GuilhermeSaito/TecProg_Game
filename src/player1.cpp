#include "player1.h"

using namespace Entidade::Player;

Player1::Player1(sf::RenderWindow *window, sf::Vector2f pos, sf::Vector2f spee, float hP, float attackDamage, const int point) : Entity(window, pos, spee, hP, attackDamage, points),
																																 contAnimation(0),
																																 score(0),
																																 player1View(NULL)
{
	if (!player1Image.loadFromFile("src/data/players/Player1Image.png"))
		EXIT_FAILURE;
	if (!openMenufont.loadFromFile("src/data/fonts/TurretRoad-Medium.ttf"))
		EXIT_FAILURE;

	rect.setPosition(pos);

	sprite.setTexture(player1Image);
	sprite.setPosition(rect.getPosition());

	healthBar.setFillColor(sf::Color::Blue);

	textScore.setFont(openMenufont);
	textScore.setCharacterSize(30);
	textScore.setString("Score: " + std::to_string(score));
}
Player1::~Player1()
{
	player1View = NULL;
	window = NULL;
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

void Player1::draw()
{
	if (player1View != NULL)
		textScore.setPosition(player1View->getCenter().x + 48 * 8, player1View->getCenter().y - 48 * 7);
	window->draw(textScore);
	window->draw(healthBar);

	window->draw(sprite);
}

void Player1::setPlayer1View(sf::View *player1View) { this->player1View = player1View; }

void Player1::setScore(const int s) { score = s; }
const int Player1::getScore() const { return score; }
void Player1::updateScore(const int somaPontos)
{
	score += somaPontos;
	textScore.setString("Score: " + std::to_string(score));
}

json Player1::getSave()
{
	json j;
	j["players1"]["player1PositionX"] = position.x;
	j["players1"]["player1PositionY"] = position.y;
	j["players1"]["hp"] = hp;
	j["players1"]["score"] = score;

	return j;
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