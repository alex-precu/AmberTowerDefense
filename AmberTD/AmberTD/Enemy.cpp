#include "Enemy.h"

int Enemy::GetHP()
{
	return hp;
}

float Enemy::GetSpeed()
{
	return speed;
}

Enemy::Enemy(int xPos, int yPos)
{
	this->setRadius(ENEMY_SIZE);
	this->setPosition(xPos, yPos);
	this->setFillColor(sf::Color(0, 0, 255));
}
Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}
