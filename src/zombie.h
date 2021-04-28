#pragma once

#include "enemyEntity.h"

#include "player1.h"

#define ZOMBIE 31
#define ZOMBIE_POINTS 30
#define ZOMBIE_RESURRECTION_QUANTITY 5

namespace Entidade
{
	namespace Enemy
	{
		class Zombie : public EnemyEntity
		{
		private:
			sf::Texture zombieTexture;
			int resurrectionQuantity;
			const float initialHp;

		public:
			Zombie(sf::RenderWindow *window = NULL, sf::Vector2f pos = {0, 0}, sf::Vector2f spee = {0, 0}, float hP = 0, float attackDamage = 0, const int point = 0, const int rQt = 0);
			~Zombie();

			void movimentation(sf::Vector2f playerPosition);
			void update(Entidade::Player::Player1 *p) override;
			void render() override;

			//apenas por ser um método padrão dos inimigos, porém Zumbis retornam NULL
			Lists::ProjectilesList *getProjectiles();

			json getSave() override;
		};
	}
}
