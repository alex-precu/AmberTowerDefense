#pragma once
#include "Actor.h"
#include <string>
#include <vector>
class Bullet : public Actor
{
	float damage;
	std::string element;
	float elementalDamage;
	//I have no fucking clue

public:
	void Update();
	Bullet(float damage);
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

