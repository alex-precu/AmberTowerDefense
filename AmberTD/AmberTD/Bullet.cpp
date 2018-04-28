#include "Bullet.h"



void Bullet::Update()
{

}
Bullet::Bullet(float damage)
{

}
Bullet::Bullet(float damage, std::string element, float elementalDamage)
{

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


}


