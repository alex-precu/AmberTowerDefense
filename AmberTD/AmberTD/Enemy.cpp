#include "Enemy.h"

int Enemy::GetHP()
{
	return hp;
}

int Enemy::GetSpeed()
{
	return speed;
}

Enemy::Enemy(int xPos, int yPos, EnemyType type) : hp{ 100 }, speed{ 2.66 }, value{200}, previousPath{nullptr}, nextPath{nullptr}, isDestinationreached{true}, currentPath{nullptr}
{
	this->setPointCount(6);
	this->setPoint(0, sf::Vector2f(TILE_SIZE / 2, 25));
	this->setPoint(1, sf::Vector2f(TILE_SIZE -30 , TILE_SIZE/4));
	this->setPoint(2, sf::Vector2f(TILE_SIZE -30 , TILE_SIZE*0.75 ));
	this->setPoint(3, sf::Vector2f(TILE_SIZE / 2, TILE_SIZE -25 ));
	this->setPoint(4, sf::Vector2f(15, TILE_SIZE*0.75 ));
	this->setPoint(5, sf::Vector2f(15 , TILE_SIZE/4));
	this->setPosition(xPos, yPos);
	this->setOrigin(TILE_SIZE/2, TILE_SIZE/2);
	this->setFillColor(sf::Color::Magenta);

	/*if (type == EnemyType::normal)
	{
		this->setFillColor(sf::Color(0, 255 ,255));
	}
	else
	{
		this->setFillColor(type == EnemyType::fast ? sf::Color(255, 255, 0) : sf::Color(0, 0, 0));
	}*/

}

void Enemy::Update()
{
	if (nextPath)
	{
		sf::Vector2f dirrection = nextPath->getPosition() - this->getPosition();
		float lenght = (float)sqrt(pow(dirrection.x, 2) + pow(dirrection.y,2));
		if (lenght < 5)
		{
			isDestinationreached = true;
			if (currentPath)
			{
				previousPath = currentPath;
			}

			currentPath = nextPath;
			nextPath = nullptr;
			return;
		}

		dirrection.x /= lenght;
		dirrection.y /= lenght;
		dirrection.x *= speed;
		dirrection.y *= speed;
		this->setPosition(this->getPosition()+dirrection);
	}
}

void Enemy::GiveDamage(int damage)
{
	this->hp -= damage;
}
int Enemy::GetValue()
{
	return value;
}
Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}
