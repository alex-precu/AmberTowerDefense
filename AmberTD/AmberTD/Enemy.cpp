#include "Enemy.h"

int Enemy::GetHP()
{
	return hp;
}

int Enemy::GetSpeed()
{
	return speed;
}

Enemy::Enemy(int xPos, int yPos, EnemyType type) : hp{ 100 }, speed{ 80 }
{
	this->setPointCount(6);
	this->setPoint(0, sf::Vector2f(TILE_SIZE / 2, 0));
	this->setPoint(1, sf::Vector2f(TILE_SIZE , TILE_SIZE/4));
	this->setPoint(2, sf::Vector2f(TILE_SIZE , TILE_SIZE*0.75 ));
	this->setPoint(3, sf::Vector2f(TILE_SIZE / 2, TILE_SIZE));
	this->setPoint(4, sf::Vector2f(0, TILE_SIZE*0.75));
	this->setPoint(5, sf::Vector2f(0 , TILE_SIZE/4));
	this->setPosition(xPos, yPos);
	this->setFillColor(sf::Color(0, 255, 255));

	if (type == EnemyType::normal)
	{
		this->setFillColor(sf::Color(0, 255 ,255));
	}
	else
	{
		this->setFillColor(type == EnemyType::fast ? sf::Color(255, 255, 0) : sf::Color(0, 0, 0));
	}

}

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}
