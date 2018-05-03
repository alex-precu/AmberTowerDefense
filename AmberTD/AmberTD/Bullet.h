#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include "Tower.h"
#include "Enemy.h"
class Bullet : public sf::ConvexShape
{
	float damage;
	std::string element;
	float elementalDamage;
	float speed;
	Enemy* destination;

public:
	void Update();
	Bullet(Tower* t, Enemy* destination);
	Bullet(float damage,std::string element, float elementalDamage);
	~Bullet();
	void SetDamage(float damage);
	float GetDamage();
	void SetElement(std::string& element);
	std::string GetElement();
	void SetElementalDamage(float damage);
	float GetElementalDamage();
	bool CollisionDetect();
};

