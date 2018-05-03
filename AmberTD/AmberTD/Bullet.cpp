#include "Bullet.h"



void Bullet::Update()
{

		if (destination->getPosition().x < this->getPosition().x)
		{
			if (destination->getPosition().y < this->getPosition().y)
			{
				this->setPosition(this->getPosition().x - speed, this->getPosition().y - speed);
			}
			else
			{
				this->setPosition(this->getPosition().x - speed, this->getPosition().y + speed);
			}
		}
		else if (destination->getPosition().y < this->getPosition().y)
		{
			this->setPosition(this->getPosition().x + speed, this->getPosition().y - speed);
		}
		else
		{
			this->setPosition(this->getPosition().x + speed, this->getPosition().y + speed);
		}
	
}
Bullet::Bullet(Tower* originTower, Enemy* destination ) : speed{4} , elementalDamage{0}
{
	this->destination = destination;
	this->setPointCount(4);
	this->setPoint(0, sf::Vector2f(TILE_SIZE / 2, 10));
	this->setPoint(1, sf::Vector2f(TILE_SIZE - 10, TILE_SIZE / 2));
	this->setPoint(2, sf::Vector2f(TILE_SIZE /2, TILE_SIZE -10));
	this->setPoint(3, sf::Vector2f(TILE_SIZE / 2, TILE_SIZE - 10));
	this->setPosition(originTower->getPosition());
	this->setOrigin(TILE_SIZE / 2, TILE_SIZE / 2);
	this->setFillColor(sf::Color::Magenta);
	this->SetDamage(originTower->GetDamage());
}
Bullet::Bullet(float damage, std::string element, float elementalDamage)
{
	this->damage = damage;

}

Bullet::~Bullet()
{
}

void Bullet::SetDamage(float damage)
{
	this->damage = damage;
}

float Bullet::GetDamage()
{
	return damage;
}

void Bullet::SetElement(std::string& element)
{
	this->element = element;
}

std::string Bullet::GetElement()
{
	return element;
}

void Bullet::SetElementalDamage(float damage)
{
	elementalDamage = damage;
}

float Bullet::GetElementalDamage()
{
	return elementalDamage;
}

bool Bullet::CollisionDetect()
{

	return false;
}


